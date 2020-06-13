#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <chrono>

#include "include/Carrera.hpp"
#include "include/Estudiante.hpp"
#include "include/funciones.hpp"  

using namespace std;

//#define iteraciones 5015751
#define iteraciones 10
#define rutaAdmisionCsv "data/admision.csv"

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */

void participantes();
void imprimirCarreras(vector<Carrera>);
bool existeArchivo(string);
vector<Carrera> generarCarreras(string);
vector<Carrera> clasificarEstudiantes(string, vector<Carrera>); 

int main(int argc, char** argv) {
  auto start = chrono::system_clock::now();
  auto end = chrono::system_clock::now();
  chrono::duration<float, milli> duration = end - start;

  if (argc > 1) {
    int opcion;

    try {
      opcion = atoi(argv[1]);
    } catch (invalid_argument const& e) {
      cout << "No existe la accion " << argv[1] << endl;
    }

    if (opcion == 1) {
      if (existeArchivo(rutaAdmisionCsv)) {
        string rutaPuntajesCsv = argv[2];
        string rutaSalida = argv[3];
        
        if (existeArchivo(rutaPuntajesCsv)) {
          vector<Carrera> carreras = generarCarreras(rutaAdmisionCsv);
          Carrera::ordenarRecursivo(carreras, 0, carreras.size() - 1);

          clasificarEstudiantes(rutaPuntajesCsv, carreras);
        } else {
          cout << "No se pudo encontrar el archivo " << rutaPuntajesCsv << ". Por favor corrija la ruta y vuelta a intentarlo." << endl;
        }
      } else {
        cout << "No se pudo encontrar el archivo " << rutaAdmisionCsv << endl;
      }
      
    } else if (opcion == 2) {
      // busqueda de rut

      int rut;
      string ruta = argv[3];
      ifstream archivos(ruta);
      try {
        rut = atoi(argv[2]);
      } catch (invalid_argument const& e) {
        cout << "rut invalido " << argv[2] << endl;
      }

      if (archivos) {
        // codigo
      } else {
        participantes();
      }
    } else {
      participantes();
    }
  } else {
    participantes();
  }
  cout << duration.count() << "s" << endl;
  return EXIT_SUCCESS;
}

bool existeArchivo(string ruta) {
    ifstream f(ruta.c_str());
    return f.good();
}

void participantes() {
  cout << endl << "=== PRUEBA 2 ===" << endl;
  cout << "Sebastián Albornoz" << endl;
  cout << "Sebastián Santelices" << endl;
  cout << "Jorge Verdugo" << endl;
}

void imprimirCarreras(vector<Carrera> carreras) {
  for (int i = 0; i < carreras.size(); i++) {
    Carrera carrera = carreras[i];
    cout << carrera.getCodigo() << endl;
  }
}

vector<Carrera> generarCarreras(string rutaCsv) {
  vector<Carrera> carreras;

  ifstream entrada(rutaCsv);
  for (string linea; getline(entrada, linea);) {
    Carrera carrera = Carrera(linea);
    carreras.push_back(carrera);
  }

  return carreras;
}

vector<Carrera> clasificarEstudiantes(string rutaCsv, vector<Carrera> carreras) {
  vector<Carrera> carreraLlenas;

  ifstream input(rutaCsv);
  int i = 0;
  for (string linea; getline(input, linea) && i < iteraciones; i++) {
    Estudiante estudiante = Estudiante(linea);
    vector<pair<int, float>> carrerasPonderaciones;
    cout << "Para el estudiante " << estudiante.rut << endl;
    for (int j = 0; j < carreras.size(); j++) {
      Carrera carrera = carreras[j];
      float ponderado = carrera.valorPonderado(estudiante);
      carrerasPonderaciones.push_back(pair<int, float>(carrera.codigo, ponderado));
      //cout << "Estudiante: " << estudiante.rut << " | Carrera: " << carrera.getCodigo() << " | Ponderado: " << ponderado << endl;
    }
    ordenarRecursivo(carrerasPonderaciones, 0, carrerasPonderaciones.size());
    for (int k = 0; k < carrerasPonderaciones.size(); k++) {
      pair<int, float> carreraPonderacion = carrerasPonderaciones[k];
      cout << carreraPonderacion.first << ": " << carreraPonderacion.second << endl;
    }
  }

  return carreraLlenas;
} 