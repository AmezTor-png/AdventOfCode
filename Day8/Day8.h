#ifndef DAY8_H
#define DAY8_H

#include <ostream>
#include <vector>

using namespace std;

struct Nodo
{
    int x, y, z;
};

struct Conexiones
{
    int nodo1, nodo2;
    double distancia;
};

class Circuito
{
    private:
        vector<int> padre;
        vector<int> tamanyo;
    
    public:
        Circuito(int n);
        
        int encontrar(int x);
        void migrar(int nodo1, int nodo2);
        vector<int> getTamanyo();
};

class Grafo
{
    public:
        vector<Conexiones> tablaConexiones;
    
        void conexionesNodos(vector<Nodo> matrizNodos);
};

#endif