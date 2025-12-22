# README

## Descripción

Este programa en **C++** lee una lista de puntos `(x,y)` que definen un **polígono ortogonal** (lados solo horizontales o verticales, en orden). Calcula dos cosas:

1. **Parte 1**  
   El área máxima de un rectángulo alineado a ejes definido por **cualquier par de puntos**, sin importar si queda fuera del polígono.

2. **Parte 2**  
   El área máxima de un rectángulo alineado a ejes definido por **dos vértices del polígono** que quede **completamente dentro o sobre el borde del polígono**.

Las áreas se calculan en número de **celdas de una grilla**, por eso se suma `+1` al ancho y alto.

---

## Entrada

- Entrada estándar (`stdin`)
- Una línea por punto, formato:

```
x,y
```

Ejemplo:
```
1,1
5,1
5,4
1,4
```

Condiciones:
- El polígono se cierra automáticamente (último punto con el primero).
- Todos los lados son horizontales o verticales.
- Los puntos están en orden (horario o antihorario).
- Coordenadas enteras (`long long`).

---

## Salida

```
Parte 1: <area_maxima>
Parte 2: <area_maxima>
```

---

## Funcionamiento (resumen técnico)

### Parte 1
- Fuerza bruta `O(n²)`.
- Para cada par de puntos:
  - `ancho = |x1 - x2| + 1`
  - `alto  = |y1 - y2| + 1`
  - `area = ancho * alto`

### Parte 2

1. Construcción de aristas del polígono (verticales y horizontales).
2. Compresión de coordenadas en X e Y (puntos exactos + huecos).
3. Ray casting por filas para detectar zonas interiores.
4. Construcción de un prefijo 2D de celdas **fuera** del polígono.
5. Prueba de todos los pares de vértices:
   - Si el rectángulo no contiene celdas fuera → válido.

Complejidad aproximada:
- Tiempo: `O(n² + X·Y)`
- Memoria: `O(X·Y)`

---

## Compilación

```
g++ -O2 -std=c++17 main.cpp -o poligono
```

## Ejecución

```
./poligono < input.txt
```

---

## Notas

- No valida autointersecciones.
- Asume polígono ortogonal simple.
- Un lado no horizontal/vertical provoca error.
- Puede consumir bastante memoria con coordenadas muy dispersas.
