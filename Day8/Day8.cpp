#include "Day8_copy.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool orden(const Conexiones& a, const Conexiones& b)
{
    return a.distancia < b.distancia;
}

Circuito::Circuito(int n)
{
    //Constructor
    padre.resize(n);
    tamanyo.resize(n, 1);   

    for(int i = 0; i < n; i++)
    {
        padre[i] = i;
    }
}

int Circuito::encontrar(int nodox)
{
    if(padre[nodox] != nodox)
    {
        padre[nodox] = encontrar(padre[nodox]);
    }

    return padre[nodox];
}

void Circuito::migrar(int nodo1, int nodo2)
{
    //Encuentra el padre
    nodo1 = encontrar(nodo1);
    nodo2 = encontrar(nodo2);

    //Si los 2 nodos se encuentran en el mismo circuito, no hace nada
    if(nodo1 == nodo2)
    {
        return;
    }

    //Apuntar nodo2 a nodo1
    padre[nodo2] = nodo1;

    //Actualizar el nuevo tamaño
    tamanyo[nodo1] += tamanyo[nodo2];
}

vector<int> Circuito::getTamanyo()
{
    vector<int> independientes;

    //Devuelve el tamaño de los independientes (padres)
    for(size_t i = 0; i < padre.size(); i++)
    {
        if(padre[i] == (int)i)
        {
            independientes.push_back(tamanyo[i]);
        }
    }

    return independientes;
}

void Grafo::conexionesNodos(const vector<Nodo> matrizNodos)
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