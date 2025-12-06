#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int contarAdyacentes(const vector<string> &matriz)
{
    int adyacentes = 0;
    int accesible = 0;

    //i filas
    //j columnas
    
    for(int i = 0; i < (int)matriz.size(); i++)
    {
        for(int j = 0; j < (int)matriz[i].size(); j++)
        {
            if(matriz[i][j] == '@')
            {
                for(int ai = (i - 1); ai <= (i + 1); ai++)
                {
                    for(int aj = (j - 1); aj <= (j + 1); aj++)
                    {
                        if(ai < 0 || ai >= (int)matriz.size() || aj < 0 || aj >= (int)matriz[i].size())
                        {

                        }
                        else if(ai == i && aj == j)
                        {

                        }
                        else if(matriz[ai][aj] != '@')
                        {

                        }
                        else
                        {
                            adyacentes++;
                        }
                    }
                }
            
                if(adyacentes < 4)
                {
                    accesible++;
                }
            
                adyacentes = 0;
            }
        }
    }

    return accesible;
}

int main()
{
    vector<string> matriz;
    string linea;

    ifstream file("inputD4.txt");

    while(getline(file, linea))
    {
        matriz.push_back(linea);
    }

    file.close();

    int solucion = contarAdyacentes(matriz);

    cout << solucion;

    return 0;
}
