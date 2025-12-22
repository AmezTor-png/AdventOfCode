#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  // llabs

using namespace std;

// -------------------------
// Estructuras simples
// -------------------------

struct Punto {
    long long x;
    long long y;
};

struct Segmento1D {
    long long inicio;   // coordenada real inicio
    long long fin;      // coordenada real fin
    long long longitud; // cuántas celdas representa (fin - inicio + 1)
};

struct AristaVertical {
    long long x;
    long long y1; // min
    long long y2; // max
};

struct AristaHorizontal {
    long long y;
    long long x1; // min
    long long x2; // max
};

struct Intervalo {
    long long izq;
    long long der;
};

// -------------------------
// Funciones auxiliares
// -------------------------

// Construye segmentos para compresión:
// mete "huecos" (verde) y "puntos exactos" (rojo).
static vector<Segmento1D> construirSegmentos(vector<long long> coords) {
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    vector<Segmento1D> segs;

    for (int i = 0; i < (int)coords.size(); i++) {
        long long c = coords[i];

        // Si hay hueco con el anterior, lo añadimos como segmento (verde)
        if (i > 0) {
            long long anterior = coords[i - 1];
            if (c > anterior + 1) {
                long long ini = anterior + 1;
                long long fin = c - 1;
                segs.push_back({ini, fin, fin - ini + 1});
            }
        }

        // Segmento del punto exacto (rojo), siempre longitud 1
        segs.push_back({c, c, 1});
    }

    return segs;
}

// Devuelve el índice del segmento EXACTO (inicio==fin==coord) dentro de segs.
// Como esto es “modo novato”, hacemos búsqueda lineal.
static int buscarIndiceExacto(const vector<Segmento1D>& segs, long long coord) {
    for (int i = 0; i < (int)segs.size(); i++) {
        if (segs[i].inicio == coord && segs[i].fin == coord) {
            return i;
        }
    }
    return -1; // no encontrado (no debería pasar si el input es correcto)
}

// Acceso a prefijo 2D guardado en vector 1D
static long long& prefijo(vector<long long>& pref, int tamX, int y, int x) {
    return pref[(size_t)y * (tamX + 1) + x];
}

static long long prefijoConst(const vector<long long>& pref, int tamX, int y, int x) {
    return pref[(size_t)y * (tamX + 1) + x];
}

// Suma de "fuera" en un rectángulo de índices [xa..xb] y [ya..yb] inclusive
static long long sumaFueraEnRectangulo(const vector<long long>& pref, int tamX,
                                       int xa, int xb, int ya, int yb) {
    // Ordenamos por si vienen al revés
    if (xa > xb) swap(xa, xb);
    if (ya > yb) swap(ya, yb);

    // Fórmula clásica de prefijo 2D
    long long A = prefijoConst(pref, tamX, yb + 1, xb + 1);
    long long B = prefijoConst(pref, tamX, ya,     xb + 1);
    long long C = prefijoConst(pref, tamX, yb + 1, xa);
    long long D = prefijoConst(pref, tamX, ya,     xa);

    return A - B - C + D;
}

// -------------------------
// Programa principal
// -------------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) Leer puntos "x,y"
    vector<Punto> puntos;
    string linea;

    while (getline(cin, linea)) {
        if (linea.empty()) continue;

        size_t coma = linea.find(',');
        if (coma == string::npos) continue;

        long long x = stoll(linea.substr(0, coma));
        long long y = stoll(linea.substr(coma + 1));

        puntos.push_back({x, y});
    }

    if (puntos.empty()) return 0;

    int n = (int)puntos.size();

    // -------------------------
    // PARTE 1: máxima área por dos puntos
    // -------------------------
    long long mejorParte1 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            // +1 porque contamos celdas incluyendo los bordes
            long long ancho = llabs(puntos[i].x - puntos[j].x) + 1;
            long long alto  = llabs(puntos[i].y - puntos[j].y) + 1;

            long long area = ancho * alto;
            if (area > mejorParte1) mejorParte1 = area;
        }
    }

    // -------------------------
    // PARTE 2: máxima área dentro del polígono
    // -------------------------

    // 2.1) Construir aristas del polígono
    vector<AristaVertical> aristasV;
    vector<AristaHorizontal> aristasH;

    // También guardamos todas las X e Y de los puntos para comprimir
    vector<long long> coordsX;
    vector<long long> coordsY;
    coordsX.reserve(n);
    coordsY.reserve(n);

    for (int i = 0; i < n; i++) {
        coordsX.push_back(puntos[i].x);
        coordsY.push_back(puntos[i].y);
    }

    // Cada punto con el siguiente, y el último con el primero
    for (int i = 0; i < n; i++) {
        Punto a = puntos[i];
        Punto b = puntos[(i + 1) % n];

        if (a.x == b.x) {
            // Arista vertical
            if (a.y == b.y) continue; // por si hay repetidos
            long long y1 = min(a.y, b.y);
            long long y2 = max(a.y, b.y);
            aristasV.push_back({a.x, y1, y2});
        }
        else if (a.y == b.y) {
            // Arista horizontal
            long long x1 = min(a.x, b.x);
            long long x2 = max(a.x, b.x);
            aristasH.push_back({a.y, x1, x2});
        }
        else {
            // No debería pasar: el enunciado dice que comparten eje
            cerr << "Error: hay un lado que no es horizontal ni vertical.\n";
            return 1;
        }
    }

    // 2.2) Construir segmentos comprimidos en X e Y
    vector<Segmento1D> segX = construirSegmentos(coordsX);
    vector<Segmento1D> segY = construirSegmentos(coordsY);

    int tamX = (int)segX.size();
    int tamY = (int)segY.size();

    // 2.3) Crear prefijo 2D de "celdas fuera del polígono"
    vector<long long> pref((size_t)(tamX + 1) * (tamY + 1), 0);

    // Recorremos cada fila comprimida
    for (int iy = 0; iy < tamY; iy++) {
        long long y0 = segY[iy].inicio; // una Y representativa

        // a) Cruces con aristas verticales (ray casting)
        vector<long long> crucesX;
        crucesX.reserve(aristasV.size());

        for (int k = 0; k < (int)aristasV.size(); k++) {
            AristaVertical e = aristasV[k];

            // y0 en [y1, y2) para evitar dobles conteos en vértices
            if (y0 >= e.y1 && y0 < e.y2) {
                crucesX.push_back(e.x);
            }
        }

        sort(crucesX.begin(), crucesX.end());

        // b) Intervalos "dentro" por pares de cruces
        vector<Intervalo> intervalos;
        for (int k = 0; k + 1 < (int)crucesX.size(); k += 2) {
            long long l = crucesX[k];
            long long r = crucesX[k + 1];
            if (l > r) swap(l, r);
            intervalos.push_back({l, r});
        }

        // c) Añadir bordes horizontales en y0 (borde cuenta como dentro)
        for (int k = 0; k < (int)aristasH.size(); k++) {
            AristaHorizontal e = aristasH[k];
            if (e.y == y0) {
                intervalos.push_back({e.x1, e.x2});
            }
        }

        // d) Ordenar y unir intervalos para simplificar
        sort(intervalos.begin(), intervalos.end(),
             [](const Intervalo& a, const Intervalo& b) {
                 if (a.izq != b.izq) return a.izq < b.izq;
                 return a.der < b.der;
             });

        vector<Intervalo> unidos;
        for (int k = 0; k < (int)intervalos.size(); k++) {
            Intervalo in = intervalos[k];

            if (unidos.empty() || in.izq > unidos.back().der + 1) {
                unidos.push_back(in);
            } else {
                // se solapan o se tocan
                if (in.der > unidos.back().der) unidos.back().der = in.der;
            }
        }

        // e) Para cada columna comprimida, decidimos si el bloque está dentro
        int pos = 0; // índice en "unidos"

        for (int ix = 0; ix < tamX; ix++) {
            Segmento1D sx = segX[ix];

            // movemos "pos" hasta que el intervalo pueda cubrir sx
            while (pos < (int)unidos.size() && unidos[pos].der < sx.inicio) {
                pos++;
            }

            bool dentro = false;

            // dentro si el intervalo cubre completamente el segmento sx
            if (pos < (int)unidos.size() &&
                unidos[pos].izq <= sx.inicio &&
                unidos[pos].der >= sx.fin) {
                dentro = true;
            }

            // si no está dentro, todo el bloque cuenta como "fuera"
            long long fuera = 0;
            if (!dentro) {
                fuera = sx.longitud * segY[iy].longitud;
            }

            // actualizar prefijo (fórmula típica)
            prefijo(pref, tamX, iy + 1, ix + 1) =
                prefijo(pref, tamX, iy + 1, ix) +
                prefijo(pref, tamX, iy,     ix + 1) -
                prefijo(pref, tamX, iy,     ix) +
                fuera;
        }
    }

    // 2.4) Probar todas las parejas y comprobar si el rectángulo queda dentro
    long long mejorParte2 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            long long xMin = min(puntos[i].x, puntos[j].x);
            long long xMax = max(puntos[i].x, puntos[j].x);
            long long yMin = min(puntos[i].y, puntos[j].y);
            long long yMax = max(puntos[i].y, puntos[j].y);

            long long ancho = (xMax - xMin) + 1;
            long long alto  = (yMax - yMin) + 1;
            long long area  = ancho * alto;

            // si no mejora, pasamos
            if (area <= mejorParte2) continue;

            // convertir a índices comprimidos (buscando el segmento exacto)
            int ix1 = buscarIndiceExacto(segX, xMin);
            int ix2 = buscarIndiceExacto(segX, xMax);
            int iy1 = buscarIndiceExacto(segY, yMin);
            int iy2 = buscarIndiceExacto(segY, yMax);

            // si algo no se encuentra, algo raro hay en el input
            if (ix1 < 0 || ix2 < 0 || iy1 < 0 || iy2 < 0) continue;

            // si la suma de "fuera" es 0, entonces el rectángulo cabe entero dentro
            long long fuera = sumaFueraEnRectangulo(pref, tamX, ix1, ix2, iy1, iy2);
            if (fuera == 0) {
                mejorParte2 = area;
            }
        }
    }

    cout << "Parte 1: " << mejorParte1 << "\n";
    cout << "Parte 2: " << mejorParte2 << "\n";

    return 0;
}
