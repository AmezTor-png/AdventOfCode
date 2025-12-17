#ifndef DAY8_H
#define DAY8_H

#include <ostream>
#include <vector>

using namespace std;

struct Nodo
{
    int x, y, z;
    int circuitoActual = 0;
};

struct Conexiones
{
    int nodo1, nodo2;
    double distancia;
};

class Circuito
{
    public:
        int numNodos;
        int idCircuito;

        Circuito(int id = 0) : numNodos(0), idCircuito(id) {}
        void nuevoCircuito(int idCircuito);
        void agregarCircuito();
};

inline ostream& operator<<(ostream& os, const Circuito& circuitos)
{
    return os << "id = " << circuitos.idCircuito << " numNodos = " << circuitos.numNodos;
}

class Grafo
{
    public:
        vector<Conexiones> tablaConexiones;
    
        void conexionesNodos(vector<Nodo> matrizNodos);
};

#endif