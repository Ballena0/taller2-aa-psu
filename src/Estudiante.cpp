#include "../include/Estudiante.hpp"
#include "../include/funciones.hpp"

Estudiante::Estudiante(long _rut, int _nem, int _ranking, int _matematica, int _lenguaje, int _ciencias, int _historia) {
    rut = _rut;
    nem = _nem;
    ranking = _ranking;
    matematica = _matematica;
    lenguaje = _lenguaje;
    ciencias = _ciencias;
    historia = _historia;
}

Estudiante::Estudiante(string lineaCsv) {
    vector<string> arreglo = split(lineaCsv, ';');
    rut = stol(arreglo[0]);
    nem = stoi(arreglo[1]);
    ranking = stoi(arreglo[2]);
    matematica = stoi(arreglo[3]);
    lenguaje = stoi(arreglo[4]);
    ciencias = stoi(arreglo[5]);
    historia = stoi(arreglo[6]);
}

Estudiante::~Estudiante() {

}
