//Estrategia exhaustiva o furza bruta
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;


int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <archivo_input>\n";
        return 1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "No se pudo abrir el archivo: " << argv[1] << "\n";
        return 1;
    }

    int pos = 50;
    int zeros = 0;
    string s;
    while (getline(in, s)) {
        if (s.empty()) continue;
        char dir = toupper(s[0]);
        int dist = stoi(s.substr(1));
        if (dir == 'L') {
            pos = (pos - dist) % 100;
        } else if (dir == 'R') {
            pos = (pos + dist) % 100;
        } else {
            cerr << "Dirección inválida en línea: " << s << "\n";
            return 1;
        }
        if (pos < 0) pos += 100; // asegurar rango [0,99]
        if (pos == 0) zeros++;
    }

    cout << zeros << "\n";
    return 0;
}
