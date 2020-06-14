#include <stdio.h>
#include "../include/funciones.hpp"  

vector<string> split(string str, char delimitador) {
    vector<string> result;

    stringstream ss(str);

    while (ss.good()) {
        string substr;
        getline(ss, substr, delimitador);
        result.push_back(substr);
    }

    return result;
}

map<int, Carrera> generarCarreras(string rutaCsv) {
  map<int, Carrera> carreras;

  ifstream entrada(rutaCsv);
  for (string linea; getline(entrada, linea);)
  {
    Carrera carrera = Carrera(linea);
    carreras.insert(pair<int, Carrera>(carrera.codigo, carrera));
  }

  return carreras;
}

