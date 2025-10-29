#include "Automata.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

Automata::Automata(string nombre, bool aceptaEpsilon) {
    this->nombre = nombre;
    estados = {};
    alfabeto = {};
    estadoInicial = "";
    transiciones = {};
    estadosFinales = {};
    this->aceptaEpsilon = aceptaEpsilon;
}

Automata Automata::agregarTransicion(string estadoActual, char simbolo, string estadoSiguiente) {
    Transicion* nuevaTransicion = new Transicion();
    nuevaTransicion->estadoActual = estadoActual;
    nuevaTransicion->simbolo = string(1, simbolo);
    nuevaTransicion->estadoSiguiente = estadoSiguiente;
    string key = estadoActual + string(1, simbolo);
    transiciones[key] = nuevaTransicion;
    return *this;
}

void Automata::imprimirLista(string titulo, vector<string> lista) {
    cout << "- " << titulo << " = {";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << lista[i];
        if (i != lista.size() - 1) cout << ", ";
    }
    cout << "}\n" << endl;
}

void Automata::imprimirEstados() {
    imprimirLista("Estados", estados);
}

void Automata::imprimirAlfabeto() {
    imprimirLista("Alfabeto", alfabeto);
}

void Automata::imprimirEstadoInicial() {
    cout << "- Estado inicial = " << estadoInicial << "\n" << endl;
}

void Automata::imprimirTransiciones() {
    cout << "- Transiciones = {\n";
    size_t count = 0;
    for (const auto& p : transiciones) {
        Transicion* t = p.second;
        cout << "(" << t->estadoActual << ", " << t->simbolo << ") -> " << t->estadoSiguiente;
        if (count != transiciones.size() - 1) cout << ",\n";
        else cout << "\n";
        count++;
    }
    cout << "}\n" << endl;
}

void Automata::imprimirEstadosFinales() {
    imprimirLista("Estados finales", estadosFinales);
}

void Automata::imprimirTupla(int nivel) {
    cout << "====================================" << endl;
    cout << "- Tupla del automata: '" << nombre << "'\n" << endl;
    int i = 1;
    while (nivel > 0)
    {
        switch (i) {
        case 1: imprimirEstados(); break;
        case 2: imprimirAlfabeto(); break;
        case 3: imprimirEstadoInicial(); break;
        case 4: imprimirTransiciones(); break;
        case 5: imprimirEstadosFinales(); break;
        case 6: cout << "- Acepta Epsilon: " << (aceptaEpsilon ? "Si" : "No") << "\n\n"; break;
        }
        i++;
        nivel--;
    }
    cout << "====================================\n" << endl;
}

bool Automata::coincideSimbolo(string simboloEntrada, string simboloTransicion) {
    if (simboloTransicion == "ANY") return true;
    if (simboloTransicion.rfind("NOT(", 0) == 0) {
        string contenido = simboloTransicion.substr(4, simboloTransicion.size() - 5);
        for (char c : contenido) {
            if (simboloEntrada == string(1, c)) return false;
        }
        return true;
    }
    return simboloEntrada == simboloTransicion;
}

bool Automata::Leer(string cadena)
{
    vector<string> estadosActuales;
    estadosActuales.push_back(estadoInicial);
    if (aceptaEpsilon) {
        estadosActuales = expandirEpsilon(estadosActuales);
    }
    for (char c : cadena) {
        string simbolo(1, c);
        vector<string> siguientes;
        for (auto& p : transiciones) {
            Transicion* t = p.second;
            for (string estado : estadosActuales) {
                if (t->estadoActual == estado && coincideSimbolo(simbolo, t->simbolo)) {
                    siguientes.push_back(t->estadoSiguiente);
                }
            }
        }
        if (siguientes.empty()) {
            cout << "No hay transicion para algun estado con simbolo '" << simbolo << "'\n";
            return false;
        }
        estadosActuales = siguientes;
        if (aceptaEpsilon) {
            estadosActuales = expandirEpsilon(estadosActuales);
        }
    }
    for (string estado : estadosActuales) {
        if (esEstadoFinal(estado)) {
            cout << "La cadena '" << cadena << "' es aceptada por el automata.\n";
            return true;
        }
    }
    cout << "La cadena '" << cadena << "' no es aceptada por el automata.\n";
    return false;
}

bool Automata::esEstadoFinal(string estado)
{
    for (const string& estadoFinal : estadosFinales) {
        if (estado == estadoFinal) {
            return true;
        }
    }
    return false;
}

vector<string> Automata::expandirEpsilon(vector<string> estados) {
    vector<string> resultado = estados;
    for (size_t i = 0; i < resultado.size(); i++) {
        string estado = resultado[i];
        string key = estado + "";
        if (transiciones.find(key) != transiciones.end()) {
            string siguiente = transiciones[key]->estadoSiguiente;
            if (!siguiente.empty()) {
                bool existe = false;
                for (size_t j = 0; j < resultado.size(); j++) {
                    if (resultado[j] == siguiente) {
                        existe = true;
                        break;
                    }
                }
                if (!existe) {
                    resultado.push_back(siguiente);
                }
            }
        }
    }
    return resultado;
}