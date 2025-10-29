#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace std {
    struct Transicion {
        string estadoActual;
        string simbolo;
        string estadoSiguiente;
    };

    class Automata {
    public:
        string nombre;
        vector<string> estados;
        vector<string> alfabeto;
        string estadoInicial;
        map<string, Transicion*> transiciones;
        vector<string> estadosFinales;
        bool aceptaEpsilon;

        Automata(string nombre, bool aceptaEpsilon);

        Automata agregarTransicion(string estadoActual, char simbolo, string estadoSiguiente);

        void imprimirEstados();
        void imprimirAlfabeto();
        void imprimirEstadoInicial();
        void imprimirTransiciones();
        void imprimirEstadosFinales();
        void imprimirTupla(int nivel);

        bool Leer(string cadena);

    private:
        void imprimirLista(string titulo, vector<string> lista);
        bool esEstadoFinal(string estado);
        vector<string> expandirEpsilon(vector<string> estados);
        bool coincideSimbolo(string simboloEntrada, string simboloTransicion);
    };
}

#endif