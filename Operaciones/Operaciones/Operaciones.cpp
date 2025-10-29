#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> generarCerradura(const string& cadena, int limite, bool incluirVacio) {
    vector<string> resultado;
    if (incluirVacio)
        resultado.push_back("");

    string acumulado = cadena;
    for (int i = 1; i <= limite; i++) {
        resultado.push_back(acumulado);
        acumulado += cadena;
    }
    return resultado;
}

int main() {
    string A, B;
    int limite;

    cout << "Ingresa la primera cadena (A): ";
    cin >> A;
    cout << "Ingresa la segunda cadena (B): ";
    cin >> B;

    cout << "Ingresa el limite para acotar las cerraduras: ";
    cin >> limite;

    if (limite <= 0) limite = 3;

    cout << "\n--- Operaciones de Autómatas Regulares ---\n";

    // Unión
    cout << "\n1. Union (A u B): { " << A << ", " << B << " }" << endl;

    // Concatenación
    cout << "\n2. Concatenacion (A B): " << A + B << endl;

    cout << "\n--- Cerraduras de A ---\n";

    // Cerradura positiva (A)
    cout << "\n3. Cerradura Positiva (A+) con limite " << limite << ": { ";
    vector<string> positivaA = generarCerradura(A, limite, false);
    for (size_t i = 0; i < positivaA.size(); i++) {
        cout << positivaA[i];
        if (i < positivaA.size() - 1) cout << ", ";
    }
    cout << " }" << endl;

    // Cerradura de Kleene (A*)
    cout << "\n4. Cerradura de Kleene (A*) con limite " << limite << ": { ";
    vector<string> kleeneA = generarCerradura(A, limite, true);
    for (size_t i = 0; i < kleeneA.size(); i++) {
        cout << (kleeneA[i] == "" ? "E" : kleeneA[i]);
        if (i < kleeneA.size() - 1) cout << ", ";
    }
    cout << " }" << endl;

    cout << "\n--- Cerraduras de B ---\n";

    cout << "\n1. Cerradura Positiva (B+) con limite " << limite << ": { ";
    vector<string> positivaB = generarCerradura(B, limite, false);
    for (size_t i = 0; i < positivaB.size(); i++) {
        cout << positivaB[i];
        if (i < positivaB.size() - 1) cout << ", ";
    }
    cout << " }" << endl;

    cout << "\n2. Cerradura de Kleene (B*) con limite " << limite << ": { ";
    vector<string> kleeneB = generarCerradura(B, limite, true);
    for (size_t i = 0; i < kleeneB.size(); i++) {
        cout << (kleeneB[i] == "" ? "E" : kleeneB[i]);
        if (i < kleeneB.size() - 1) cout << ", ";
    }
    cout << " }" << endl;

    cout << "\n------------------------------------------\n";
    return 0;
}