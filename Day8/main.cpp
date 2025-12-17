#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Day8.h"

#define MAX_CONEXIONES 1000

using namespace std;

bool orden2(const Circuito& a, const Circuito& b)
{
    return a.numNodos > b.numNodos;
}

int main()
{
    string linea;
    vector<Nodo> matrizNodos;

    Grafo grafo;

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
    grafo.conexionesNodos(matrizNodos);

    //Crear una tabla con las 1000 primeras conexiones
    vector<Circuito> matrizCircuitos;
    int idCircuito = 1;

    for(int i = 0; i < MAX_CONEXIONES; i++)
    {
        int nodo1 = grafo.tablaConexiones[i].nodo1;
        int nodo2 = grafo.tablaConexiones[i].nodo2;
        
        //Si los nodos no tienen circuito, se crea uno
        if(matrizNodos[nodo1].circuitoActual == 0 && matrizNodos[nodo2].circuitoActual == 0)
        {
            Circuito circuitos;
            circuitos.nuevoCircuito(idCircuito);

            matrizCircuitos.push_back(circuitos);

            matrizNodos[nodo1].circuitoActual = idCircuito;
            matrizNodos[nodo2].circuitoActual = idCircuito;

            idCircuito++;
        }
    
        //Si nodo1 tiene circuito, se añade el nodo2 al circuito del nodo1
        else if(matrizNodos[nodo1].circuitoActual != 0 && matrizNodos[nodo2].circuitoActual == 0)
        {
            Circuito circuitos;
            int nuevoId = matrizNodos[nodo1].circuitoActual;
            
            for(int i = 0; i < matrizCircuitos.size(); i++)
            {
                if(matrizCircuitos[i].idCircuito == nuevoId)
                {
                    matrizCircuitos[i].agregarCircuito();
                    matrizNodos[nodo2].circuitoActual = nuevoId;
                    break;
                }
            }
        }
    
        //Viceversa
        else if(matrizNodos[nodo1].circuitoActual == 0 && matrizNodos[nodo2].circuitoActual != 0)
        {    
            Circuito circuitos;
            int nuevoId = matrizNodos[nodo1].circuitoActual;
            
            for(int i = 0; i < matrizCircuitos.size(); i++)
            {
                if(matrizCircuitos[i].idCircuito == nuevoId)
                {
                    matrizCircuitos[i].agregarCircuito();
                    matrizNodos[nodo2].circuitoActual = nuevoId;
                    break;
                }
            }        
        }
    
        //Si los dos nodos se encuentran en circuitos diferentes
        else if(matrizNodos[nodo1].circuitoActual != 0 && matrizNodos[nodo2].circuitoActual != 0 && matrizNodos[nodo1].circuitoActual != matrizNodos[nodo2].circuitoActual)
        {
            //Migrar el circuito 1 al 2
            int cirDestino = matrizNodos[nodo1].circuitoActual;
            int posDestino = 0;

            int cirMigrar = matrizNodos[nodo2].circuitoActual;
            int posMigrar = 0;

            Circuito circuitos;
            int suma = 0;

            //Extraer la posicion de cada circuito en la matriz de circuitos
            for(size_t i = 0; i < matrizCircuitos.size(); i++)
            {
                if(matrizCircuitos[i].idCircuito == cirDestino)
                {
                    posDestino = (int)i;
                }
                else if(matrizCircuitos[i].idCircuito == cirMigrar)
                {
                    posMigrar = (int)i;
                }
            }

            //Sumar el numero de nodos al origen
            matrizCircuitos[posDestino].numNodos += matrizCircuitos[posMigrar].numNodos;

            //Cambiar el id del circuito de los nodos
            for(size_t i = 0; i < matrizNodos.size(); i++)
            {
                if(matrizNodos[i].circuitoActual == cirMigrar)
                {
                    matrizNodos[i].circuitoActual = cirDestino;
                }
            }

            //Borrar el circuito migrado
            matrizCircuitos.erase(matrizCircuitos.begin() + posMigrar);
        }
    }

    //Ordenar matriz de circuitos de mayor a menor
    sort(matrizCircuitos.begin(), matrizCircuitos.end(), orden2);
    
    double solucion = 1;
    int contador = 0;
    int anterior = -1;

    for(size_t i = 0; i < matrizCircuitos.size() && contador < 3; i++)
    {
        int top = matrizCircuitos[i].numNodos;
        if(top != anterior)
        {
            solucion *= top;
            anterior = top;
            contador++;
        }
        
        cout << matrizCircuitos[i] << "\n";
    }

    cout << "Solucion: " << solucion;

    return 0;
}