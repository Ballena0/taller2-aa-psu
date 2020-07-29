#include <stdio.h>
#include <vector>
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

pair<int, string> buscarRut(vector<string> rutas, string rut) {

  for (int i = 0; i < rutas.size(); i++)
  {
    string ruta = rutas[i];
    if (existeArchivo(ruta)) {
      ifstream entrada(ruta);
      int numeroLinea = 1;
      for (string linea; getline(entrada, linea);)
      {
        if (linea.find(rut) != string::npos) {
          return pair<int, string>(numeroLinea, ruta);
        }
        numeroLinea++;
      }
    } else {
      cout << "No existe el archivo " << ruta << endl;
    }
  }
  
  
}
