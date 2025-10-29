#include <iostream>
#include <string>
using namespace std;

enum Estado { q0, q1, q2 };

int main() {
    string cinta;
    cout << "Ingresa una cadena binaria (solo 0 y 1): ";
    cin >> cinta;

    int flecha = 0;
    Estado estado = q0;
    bool detener = false;

    while (!detener) {
        cout << "Estado: ";
        switch (estado) {
        case q0: cout << "q0"; break;
        case q1: cout << "q1"; break;
        case q2: cout << "q2"; break;
        }
        cout << ", Cinta: " << cinta << endl;

        switch (estado) {
        case q0:
            if (cinta[flecha] == '0') {
                cinta[flecha] = '1';
                flecha++;
            }
            else if (cinta[flecha] == '1') {
                cinta[flecha] = '0';
                flecha++;
            }
            else {
                return 1;
            }

            if (flecha >= cinta.length()) {
                flecha--;
                estado = q1;
            }
            break;

        case q1:
            if (flecha > 0) {
                flecha--;
            }
            else {
                estado = q2;
            }
            break;

        case q2:
            detener = true;
            break;
        }
    }

    cout << "Cinta final: " << cinta << endl;
    cout << "Estado final: q2" << endl;

    return 0;
}