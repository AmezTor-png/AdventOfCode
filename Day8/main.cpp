#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Day8_copy.h"

#define MAX_CONEXIONES 1000

using namespace std;

bool orden(const int& a, const int& b)
{
    return a > b;
}

int main()
{
    string linea;
    vector<Nodo> matrizNodos;

    Grafo grafos;

    //Abrir archivo
    ifstream file("inputD8.txt");

    while(getline(file, linea))
    {
        Nodo nodos;
        
        int pos = 0;

        //Extraer del input x, y, z y añadirlo a una matriz con todos los valores
        nodos.x = stoi(linea.substr(0, linea.find(',')));
        pos = linea.find(',') + 1;
        nodos.y = stoi(linea.substr(pos, linea.find(',', pos) - pos));
        pos = linea.find(',', pos) + 1;
        nodos.z = stoi(linea.substr(pos));

        //Añadirlos a la matriz
        matrizNodos.push_back(nodos);
    }

    file.close();

    //Hacer la conexion entre todos los nodos, y ordenado
    grafos.conexionesNodos(matrizNodos);

    //Inicializar circuitos con el constructor
    Circuito circuitos(matrizNodos.size());

    //Para las 1000 primeras conexiones, hacer circuitos, DSU
    for(int i = 0; i < MAX_CONEXIONES && i < (int)grafos.tablaConexiones.size(); i++)
    {
        circuitos.migrar(grafos.tablaConexiones[i].nodo1, grafos.tablaConexiones[i].nodo2);
    }

    //Tamaño de todos los circuitos
    vector<int> tamanyos = circuitos.getTamanyo();

    //Ordenar de mayor a menor
    sort(tamanyos.begin(), tamanyos.end(), orden);

    //Calcular el producto del tamaño de los 3 circuitos más grandes
    double solucion = 1;
    
    for(int i = 0; i < 3; i++)
    {
        solucion *= tamanyos[i];
    }

    cout << "Solucion: " << solucion << endl;

    return 0;
}