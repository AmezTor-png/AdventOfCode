#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>

using namespace std;

struct Nodo
{
    int x, y, z;
    int circuito;
};

struct Conexion
{
    double distancia;
};

struct Circuito
{
    int id;
    vector<int> nodos;
};

class Grafo
{
    public:
        void llenarNodos(const vector<vector<double>> &entrada);

        void guardarConexion(const Conexion& conexion);

        void crearTablaConexiones();

        int crearCircuito(int nodo1, int nodo2);

        void migrarCircuito(int origen, int destino);

        vector<Nodo> &nodos() { return nodos; }

        vector<Conexion> &conexiones() { return conexiones; }

        vector<> &circuitos() { return circuitos; }

        int contadorHash() { return contadorHash; }

    private:
        vector<Nodo> nodos;
        vector<Conexion> conexiones;
        vector<Circuito> circuitos;

        int contadorHash;
};

#endif