#include "Grafo.h"

#include <iostream>

using namespace std;

void Grafo::llenarNodos(const vector<vector<double>> &entrada)
{
    contadorHash = 1;

    for(int i = 0; i < entrada.size(); i++)
    {
        Nodo n;
        n.x = entrada[i][0];
        n.y = entrada[i][1];
        n.z = entrada[i][2];

        n.circuito = 0;

        nodos.push_back(n);
    }
}

void Grafo::guardarConexion(const Conexion& conexion)
{
    //ayudarme con esto
}

void Grafo::crearTablaConexiones()
{
    
}