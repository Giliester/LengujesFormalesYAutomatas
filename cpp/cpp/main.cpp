#include "Automata.h"

using namespace std;

map<string, Automata*> automatas;
string nuevoAutomata;

static int leerOpcion() {
    while (true) {
        string input;
        getline(cin, input);

        if (input.empty()) {
            cout << "Opcion vacia, ingrese un numero: ";
            continue;
        }

        bool esNumero = true;
        for (char c : input) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (!esNumero) {
            cout << "Entrada invalida, ingrese un numero: ";
            continue;
        }
        system("cls");
        return stoi(input);
    }
}

void Menu();
void AutomatasPrueba();
void NuevoAutomata(string nombre);
void NuevoAutomata_Estados(string nombre);
void NuevoAutomata_Alfabeto(string nombre);
void NuevoAutomata_EstadoInicial(string nombre);
void NuevoAutomata_Transiciones(string nombre);
void NuevoAutomata_EstadosFinales(string nombre);
void NuevoAutomata_Tipo(string nombre);
void NuevoAutomata_ImprimirTupla(string nombre);
void CargarAutomata();

void AutomatasPrueba() {
    Automata* A1 = new Automata("Comentario C++", false);
    A1->estados = { "q0", "q1", "q2", "q3", "q4" };
    A1->alfabeto = { "/", "*", "ANY", "NOT(/*)" };
    A1->estadoInicial = "q0";
    A1->estadosFinales = { "q4" };
    A1->agregarTransicion("q0", '/', "q1");
    A1->agregarTransicion("q1", '*', "q2");
    A1->transiciones["q2NOT(/*)"] = new Transicion{ "q2", "NOT(/*)", "q2" };
    A1->agregarTransicion("q2", '*', "q3");
    A1->agregarTransicion("q3", '/', "q4");
    A1->transiciones["q3NOT(/*)"] = new Transicion{ "q3", "NOT(/*)", "q2" };
	automatas[A1->nombre] = A1;


    Automata* A2 = new Automata("Cadena impar a", false);
    A2->estados ={ "E", "O" };
    A2->alfabeto = { "a", "b" };
    A2->estadoInicial = "E";
    A2->agregarTransicion("E", 'a', "O");
    A2->agregarTransicion("E", 'b', "E");
    A2->agregarTransicion("O", 'a', "E");
    A2->agregarTransicion("O", 'b', "O");
    A2->estadosFinales = { "O" };
    automatas[A2->nombre] = A2;
}

void Menu() {
    while (true) {
        system("cls");
        cout << "=== Automatas ===\n\n";
        cout << "Seleccione una opcion:\n";

        if (nuevoAutomata.empty()) {
            cout << "1. Nuevo Automata\n";
            cout << "2. Cargar Automata\n";
            cout << "3. Salir\n";
            int opcion = leerOpcion();
            switch (opcion) {
            case 1:
                NuevoAutomata("");
                break;
            case 2:
                CargarAutomata();
                break;
            case 3:
                exit(0);
                return;
            default:
                cout << "Opcion invalida\n";
                system("pause");
                Menu();
                break;
            }
        }
        else {
            cout << "1. Nuevo Automata\n";
            cout << "2. Cargar Automata\n";
            cout << "3. Continuar Automata (" << nuevoAutomata << ")\n";
            cout << "4. Salir\n";
            int opcion = leerOpcion();
            switch (opcion) {
            case 1:
                automatas.erase(nuevoAutomata);
                NuevoAutomata("");
                break;
            case 2:
                CargarAutomata();
                break;
            case 3:
                NuevoAutomata(nuevoAutomata);
                break;
            case 4:
                exit(0);
                return;
            default:
                cout << "Opcion invalida\n";
                system("pause");
                Menu();
                break;
            }
        }
    }
}

void NuevoAutomata(string nombre) {
    system("cls");
    if (nombre.empty()) {
        cout << "=== Nuevo automata ===\n\n";
        cout << "Ingrese el nombre del automata: ";
        string name;
        getline(cin, name);

        if (automatas.find(name) != automatas.end()) {
            cout << "El automata ya existe\n";
            system("pause");
            return NuevoAutomata("");
        }

        automatas[name] = new Automata(name, false);
        nuevoAutomata = name;
        nombre = name;
    }

    NuevoAutomata_Estados(nombre);
    NuevoAutomata_Alfabeto(nombre);
    NuevoAutomata_EstadoInicial(nombre);
    NuevoAutomata_Transiciones(nombre);
    NuevoAutomata_EstadosFinales(nombre);
    NuevoAutomata_Tipo(nombre);
    NuevoAutomata_ImprimirTupla(nombre);

    cout << "\nAutomata '" << nombre << "' creado con exito!\n";
    nuevoAutomata = "";
    system("pause");
}

void NuevoAutomata_Estados(string nombre) {
    if (!automatas[nombre]->estados.empty()) return;

    vector<string> estados;
    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
    cout << "--- Estados ---\n";
    cout << "Seleccione una opcion:\n";
    cout << "1. Agregar estado individualmente\n";
    cout << "2. Agregar varios estados\n";
    cout << "3. Volver al menu principal\n";
    int opcion = leerOpcion();
    int seleccion;
    bool finalizar = false;
    string estado;

    switch (opcion) {
    case 1: {
        while (!finalizar) {
            system("cls");
            cout << "Seleccione una opcion:\n";
            cout << "1. Agregar estado\n";
            cout << "2. Finalizar\n";
            seleccion = leerOpcion();
            switch (seleccion)
            {
            case 1:
                cout << "Ingrese el estado: ";
                getline(cin, estado);
                estados.push_back(estado);
                break;
                break;
            case 2:
                finalizar = true;
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
                break;
            }
        }
        break;
    }
    case 2: {
        cout << "Ingrese los estados separados por espacio: ";
        string linea;
        getline(cin, linea);
        size_t pos = 0;
        while ((pos = linea.find(' ')) != string::npos) {
            estados.push_back(linea.substr(0, pos));
            linea.erase(0, pos + 1);
        }
        if (!linea.empty()) estados.push_back(linea);
        break;
    }
    case 3:
        Menu();
        return;
    default:
        cout << "Opcion invalida\n";
        system("pause");
        return NuevoAutomata_Estados(nombre);
    }

    automatas[nombre]->estados = estados;
}

void NuevoAutomata_Alfabeto(string nombre) {
    if (!automatas[nombre]->alfabeto.empty()) return;

    vector<string> alfabeto;
    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
	automatas[nombre]->imprimirTupla(1);

    cout << "--- Alfabeto ---\n";
    cout << "Seleccione una opcion:\n";
    cout << "1. Agregar simbolo individualmente\n";
    cout << "2. Agregar varios simbolos\n";
    cout << "3. Volver al menu principal\n";
    int opcion = leerOpcion();
    bool finalizar = false;
    string simbolo;

    switch (opcion) {
    case 1: {
        while (!finalizar) {
            system("cls");
            cout << "Seleccione una opcion:\n";
            cout << "1. Agregar simbolo\n";
            cout << "2. Finalizar\n";
            int seleccion = leerOpcion();
            switch (seleccion) {
            case 1:
                cout << "Ingrese el simbolo: ";
                getline(cin, simbolo);
                alfabeto.push_back(simbolo);
                break;
            case 2:
                finalizar = true;
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
                break;
            }
        }
        break;
    }
    case 2: {
        cout << "Ingrese los simbolos separados por espacio: ";
        string linea;
        getline(cin, linea);
        size_t pos = 0;
        while ((pos = linea.find(' ')) != string::npos) {
            alfabeto.push_back(linea.substr(0, pos));
            linea.erase(0, pos + 1);
        }
        if (!linea.empty()) alfabeto.push_back(linea);
        break;
    }
    case 3:
        Menu();
        return;
        break;
    default:
        cout << "Opcion invalida\n"; system("pause"); return NuevoAutomata_Alfabeto(nombre);
    }

    automatas[nombre]->alfabeto = alfabeto;
}

void NuevoAutomata_EstadoInicial(string nombre) {
    if (!automatas[nombre]->estadoInicial.empty()) return;

    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
	automatas[nombre]->imprimirTupla(2);

    cout << "--- Estado inicial ---\n";
    cout << "Seleccione una opcion:\n";
    cout << "1. Ingresar estado inicial\n";
    cout << "2. Volver al menu principal\n";
    int opcion = leerOpcion();
    string estadoInicial;
    switch (opcion) {
    case 1:
        system("cls");
        cout << "Ingrese el estado inicial: ";
        getline(cin, estadoInicial);
        break;
    case 2:
        Menu();
        return;
        break;
    default:
        cout << "Opcion invalida\n";
        system("pause");
        return NuevoAutomata_EstadoInicial(nombre);
    }
    automatas[nombre]->estadoInicial = estadoInicial;
}

void NuevoAutomata_Transiciones(string nombre) {
    if (!automatas[nombre]->transiciones.empty()) return;

    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
	automatas[nombre]->imprimirTupla(3);

    cout << "--- Transiciones ---\n";
    cout << "Seleccione una opcion:\n";
    cout << "1. Agregar transicion\n";
    cout << "2. Volver al menu principal\n";
    int opcion = leerOpcion();
    bool finalizar = false;
    string estadoActual, simbolo, estadoSiguiente;

    switch (opcion) {
    case 1:
        while (!finalizar) {
            system("cls");
            cout << "Seleccione una opcion:\n";
            cout << "1. Agregar transicion\n";
            cout << "2. Finalizar\n";
            int seleccion = leerOpcion();
            switch (seleccion) {
            case 1:
                cout << "Ingrese el estado actual: ";
                getline(cin, estadoActual);
                cout << "Ingrese el simbolo: ";
                getline(cin, simbolo);
                cout << "Ingrese el estado siguiente: ";
                getline(cin, estadoSiguiente);
                automatas[nombre]->agregarTransicion(estadoActual, simbolo[0], estadoSiguiente);
                break;
            case 2:
                finalizar = true;
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
                break;
            }
        }
        break;
    case 2:
        Menu();
        return;
        break;
    default:
        cout << "Opcion invalida\n";
        system("pause");
        return NuevoAutomata_Transiciones(nombre);
    }
}

void NuevoAutomata_EstadosFinales(string nombre) {
    if (!automatas[nombre]->estadosFinales.empty()) return;

    vector<string> estadosFinales;
    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
	automatas[nombre]->imprimirTupla(4);

    cout << "--- Estados finales ---\n";
    cout << "Seleccione una opcion:\n";
    cout << "1. Agregar estado final individualmente\n";
    cout << "2. Agregar varios estados finales\n";
    cout << "3. Volver al menu principal\n";
    int opcion = leerOpcion();
    bool finalizar = false;
    string estadoFinal;
    switch (opcion) {
    case 1: {
        while (!finalizar) {
            system("cls");
            cout << "Seleccione una opcion:\n";
            cout << "1. Agregar estado final\n";
            cout << "2. Finalizar\n";
            int seleccion = leerOpcion();
            switch (seleccion) {
            case 1:
                cout << "Ingrese el estado final: ";
                getline(cin, estadoFinal);
                estadosFinales.push_back(estadoFinal);
                break;
            case 2:
                finalizar = true;
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
                break;
            }
        }
        break;
    }
    case 2: {
        cout << "Ingrese los estados finales separados por espacio: ";
        string linea;
        getline(cin, linea);
        size_t pos = 0;
        while ((pos = linea.find(' ')) != string::npos) {
            estadosFinales.push_back(linea.substr(0, pos));
            linea.erase(0, pos + 1);
        }
        if (!linea.empty()) estadosFinales.push_back(linea);
        break;
    }
    case 3:
        Menu();
        return;
    default:
        cout << "Opcion invalida\n";
        system("pause");
        return NuevoAutomata_EstadosFinales(nombre);
    }

    automatas[nombre]->estadosFinales = estadosFinales;
}

void NuevoAutomata_Tipo(string nombre) {
    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
    automatas[nombre]->imprimirTupla(5);

    cout << "--- Tipo ---\n";
    cout << "Seleccione una opcion:\n";
    cout << "1. El automata contiene transiciones epsilon\n";
    cout << "2. El automata no contiene transiciones epsilon\n";
    cout << "3. Volver al menu principal\n";
    int opcion = leerOpcion();
    switch (opcion) {
    case 1:
        automatas[nombre]->aceptaEpsilon = true;
        break;
    case 2:
        automatas[nombre]->aceptaEpsilon = false;
        break;
    case 3:
        Menu();
        return;
    default:
        cout << "Opcion invalida\n";
        system("pause");
        return NuevoAutomata_Tipo(nombre);
    }
}

void NuevoAutomata_ImprimirTupla(string nombre) {
    system("cls");
    cout << "=== Nuevo automata (" << nombre << ") ===\n\n";
    automatas[nombre]->imprimirTupla(6);
    system("pause");
}

void CargarAutomata() {
    system("cls");
    int count = 1;
    cout << "=== Cargar automata ===\n\n";
    cout << "Seleccione un automata:\n";
    if (automatas.empty()) {
        cout << "No hay automatas disponibles\n";
        system("pause");
        Menu();
        return;
    }
    else {
        for (const auto& p : automatas) {
            const string& key = p.first;
            cout << count << ". " << key << "\n";
            count++;
        }
    }
    cout << count << ". Volver al menu principal\n";
    int opcion = leerOpcion();
    if (opcion == count) {
        Menu();
        return;
    }
    if (opcion < 1 || opcion >= count) {
        cout << "Opcion invalida\n";
        system("pause");
        return CargarAutomata();
    }
    else {
        auto it = automatas.begin();
        advance(it, opcion - 1);
        string nombre = it->first;
        cout << "Automata '" << nombre << "' cargado con exito!\n";
        automatas[nombre]->imprimirTupla(6);
        cout << "Seleccione una opcion:\n";
        cout << "1. Probar cadena\n";
        cout << "2. Volver al menu principal\n";
        int opcion2 = leerOpcion();
        switch (opcion2) {
        case 1: {
            cout << "Ingrese la cadena a probar: ";
            string cadena;
            getline(cin, cadena);
            automatas[nombre]->Leer(cadena);
            break;
        }
        case 2:
            Menu();
            return;
        default:
            cout << "Opcion invalida\n";
            system("pause");
            return CargarAutomata();
        }
    }
    system("pause");
}

int main() {
    AutomatasPrueba();
    Menu();
    return 0;
}