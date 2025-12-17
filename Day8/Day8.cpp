#include "Day8.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool orden(const Conexiones& a, const Conexiones& b)
{
    return a.distancia < b.distancia;
}

void Grafo::conexionesNodos(vector<Nodo> matrizNodos)
{
    for(size_t i = 0; i < matrizNodos.size(); i++)
    {
        //Extraer posición primer nodo
        const int x1 = matrizNodos[i].x;
        const int y1 = matrizNodos[i].y;
        const int z1 = matrizNodos[i].z;
        
        for(size_t j = i + 1; j < matrizNodos.size(); j++)
        {
            //Extraer posición segundo nodo
            const int x2 = matrizNodos[j].x;
            const int y2 = matrizNodos[j].y;
            const int z2 = matrizNodos[j].z;

            double distancia = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));

            //Almacenarlo en la tabla de conexiones
            tablaConexiones.push_back({(int)i, (int)j, distancia});
        }
    }

    //Ordenar la tablaConexiones de menor a mayor distancia
    sort(tablaConexiones.begin(), tablaConexiones.end(), orden);
}

void Circuito::nuevoCircuito(int nuevoId)
{
    numNodos = 2;
    idCircuito = nuevoId;
}

void Circuito::agregarCircuito()
{
    numNodos++;
}