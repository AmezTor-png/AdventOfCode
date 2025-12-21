#include <iostream>
#include <fstream>
#include <string>

#include "Day5.h"

using namespace std;

int main() {
    ifstream archivo("input.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return 1;
    }

    string linea;
    IntervalNode* root = nullptr;

    // Leer rangos e insertarlos en el árbol
    while (getline(archivo, linea) && !linea.empty()) {
        int pos = linea.find('-');
        long long a = stoll(linea.substr(0, pos));
        long long b = stoll(linea.substr(pos + 1));
        root = insert(root, a, b);
    }

    long long frescos = 0;

    // Leer IDs y contar cuántos son frescos
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        long long id = stoll(linea);
        if (contains(root, id)) {
            frescos++;
        }
    }

    cout << "Solucion: " << frescos << "\n";

    archivo.close();

    return 0;
}
