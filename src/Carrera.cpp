#include "../include/Carrera.hpp"
#include "../include/funciones.hpp"

Carrera::Carrera() {

}

Carrera::Carrera(int _codigo, int _nem, int _ranking, int _lenguaje, int _matematica, int _ciencias, int _promedioMinimo, int _vacantes, float _primero, float _ultimo) {
    codigo = _codigo;
    nem = _nem;
    ranking = _ranking;
    lenguaje = _lenguaje;
    matematica = _matematica;
    ciencias = _ciencias;
    promedioMinimo = _promedioMinimo;
    vacantesTotales = _vacantes;
    vacantesActuales = _vacantes;
    primero = _primero;
    ultimo = _ultimo;
}

Carrera::Carrera(string lineaCsv) {
    vector<string> arreglo = split(lineaCsv, ',');
    codigo = stoi(arreglo[0]);
    nem = stoi(arreglo[1]);
    ranking = stoi(arreglo[2]);
    lenguaje = stoi(arreglo[3]);
    matematica = stoi(arreglo[4]);
    ciencias = stoi(arreglo[5]);
    promedioMinimo = stoi(arreglo[6]);
    vacantesTotales = stoi(arreglo[7]);
    vacantesActuales = stoi(arreglo[7]);
    primero = stof(arreglo[8]);
    ultimo = stof(arreglo[9]);
}

Carrera::~Carrera() {

}

int Carrera::getCodigo() {
    return codigo;
}

float Carrera::valorPonderado(Estudiante e) {
    return (nem * e.nem + ranking * e.ranking + lenguaje * e.lenguaje + matematica * e.matematica + ciencias * e.ciencias) / 100;
}

bool Carrera::estaLlena() {
    return vacantesActuales <= 0;
}

bool Carrera::estaVacia() {
    return vacantesActuales == vacantesTotales;
}

bool Carrera::agregarEstudiante(Estudiante e) {
    if (!estaLlena()) {
        estudiantes.push_back(e);
        vacantesActuales--;
        return true;
    }
    
    return false;
}

bool Carrera::operator > (const Carrera &c) const {
    if (primero == c.primero) {
        if (vacantesTotales == c.vacantesTotales) {
            if (ultimo == c.ultimo) {
                return false;
            }
            return ultimo > c.ultimo;
        }
        return vacantesTotales > c.vacantesTotales;
    }
    return primero > c.primero;
}

bool Carrera::operator < (const Carrera &c) const {
    if (primero == c.primero) { 
        if (vacantesTotales == c.vacantesTotales) {
            if (ultimo == c.ultimo) {
                return false;
            }
            return ultimo < c.ultimo;
        }
        return vacantesTotales < c.vacantesTotales;
    }
    return primero < c.primero;
}

bool Carrera::operator >= (const Carrera &c) const {
    if (primero == c.primero) {
        if (vacantesTotales == c.vacantesTotales) {
            if (ultimo == c.ultimo) {
                return true;
            }
            return ultimo > c.ultimo;
        }
        return vacantesTotales > c.vacantesTotales;
    }
    return primero > c.primero;
}

bool Carrera::operator <= (const Carrera &c) const {
    if (primero == c.primero) {
        if (vacantesTotales == c.vacantesTotales) {
            if (ultimo == c.ultimo) {
                return true;
            }
            return ultimo < c.ultimo;
        }
        return vacantesTotales < c.vacantesTotales;
    }
    return primero < c.primero;
}

vector<Estudiante> Carrera::getEstudiantes(){
    return estudiantes;
}