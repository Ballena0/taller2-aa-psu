#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <chrono>

#include "include/Carrera.hpp"
#include "include/Estudiante.hpp"
#include "include/EstudianteCarrera.hpp"
#include "include/funciones.hpp"

using namespace std;

//#define iteraciones 5015751
#define iteraciones 200
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
bool quedanVacantesDisponibles(map<int, Carrera>);
void clasificarEstudiantes(string, map<int, Carrera>&);
void escribirCarreras(vector<Carrera> listaCarreras, string rutaSalida);

int main(int argc, char **argv)
{
  auto start = chrono::system_clock::now();
  auto end = chrono::system_clock::now();
  chrono::duration<float, milli> duration = end - start;

  if (argc > 1)
  {
    int opcion;

    try
    {
      opcion = atoi(argv[1]);
    }
    catch (invalid_argument const &e)
    {
      cout << "No existe la accion " << argv[1] << endl;
    }

    if (opcion == 1)
    {
      if (existeArchivo(rutaAdmisionCsv))
      {
        string rutaPuntajesCsv = argv[2];
        string rutaSalida = argv[3];
        
        if (existeArchivo(rutaPuntajesCsv)) {
          map<int, Carrera> carreras = generarCarreras(rutaAdmisionCsv);
          clasificarEstudiantes(rutaPuntajesCsv, carreras);
        }
        else
        {
          cout << "No se pudo encontrar el archivo " << rutaPuntajesCsv << ". Por favor corrija la ruta y vuelta a intentarlo." << endl;
        }
      }
      else
      {
        cout << "No se pudo encontrar el archivo " << rutaAdmisionCsv << endl;
      }
    }
    else if (opcion == 2)
    {
      // busqueda de rut

      int rut;
      string ruta = argv[3];
      ifstream archivos(ruta);
      try
      {
        rut = atoi(argv[2]);
      }
      catch (invalid_argument const &e)
      {
        cout << "rut invalido " << argv[2] << endl;
      }

      if (archivos)
      {
        // codigo
      }
      else
      {
        participantes();
      }
    }
    else
    {
      participantes();
    }
  }
  else
  {
    participantes();
  }
  cout << duration.count() << "s" << endl;
  return EXIT_SUCCESS;
}

bool existeArchivo(string ruta)
{
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

void clasificarEstudiantes(string rutaCsv, map<int, Carrera> &carreras) {
  map<long, Estudiante> estudiantesAsignados;
  vector<EstudianteCarrera> estudiantesCarreras;

  ifstream input(rutaCsv);
  int i = 0;
  for (string linea; getline(input, linea) && i < iteraciones; i++) {
    Estudiante estudiante = Estudiante(linea);
    for (auto const& c : carreras) {
      Carrera carrera = c.second;
      float ponderado = carrera.valorPonderado(estudiante);
      estudiantesCarreras.push_back(EstudianteCarrera(estudiante, carrera, ponderado));
    }
  }

  ordenarRecursivo(estudiantesCarreras, 0, estudiantesCarreras.size());
  int j = 0;
  while (quedanVacantesDisponibles(carreras) && j < estudiantesCarreras.size()) {
    EstudianteCarrera estudianteCarrera = estudiantesCarreras[j];
    Estudiante estudiante = estudianteCarrera.estudiante;
    Carrera carrera = estudianteCarrera.carrera;
    if (estudiantesAsignados.find(estudiante.rut) == estudiantesAsignados.end() ) {
      // Si aún no se asigna el usuario
      bool seAgrego = carreras[carrera.codigo].agregarEstudiante(estudiante);
      if (seAgrego) {
        cout << "Se asignó al estudiante " << estudiante.rut << " a la carrera " << carrera.codigo << " con " << estudianteCarrera.ponderado << " puntos ponderados" << endl;
        estudiantesAsignados.insert(pair<long, Estudiante>(estudiante.rut, estudiante));
      }
    }
    
    j++;
  }

    

/*#pragma omp parallel
  {
#pragma omp single
    {
      for (string linea; getline(input, linea);)
      {
#pragma omp task
        {
          Estudiante estudiante = Estudiante(linea);
          for (long unsigned int i = 0; i < carreras.size(); i++)
          {
            Carrera carrera = carreras[i];
            float ponderado = carrera.valorPonderado(estudiante);
#pragma omp critical
            cout << "Estudiante: " << estudiante.rut << " | Carrera: " << carrera.getCodigo() << " | Ponderado: " << ponderado << endl;
          }
        }
      }
    }
  }*/
  
}

bool quedanVacantesDisponibles(map<int, Carrera> carreras) {
  for (auto const& c : carreras) {
    Carrera carrera = c.second;
    if (!carrera.estaLlena()) {
      return true;
    }
  }
  return false;
}

void escribirCarreras(vector<Carrera> listaCarreras, string rutaSalida) {
    for(long unsigned int i = 0; i < listaCarreras.size(); i++){
      string nombreCarrera = rutaSalida + std::to_string(listaCarreras[i].getCodigo()) + ".txt";
      ofstream salida(nombreCarrera, fstream::app);
      for(long unsigned int j = 0; i < listaCarreras[i].getEstudiantes().size(); j++){
          salida << listaCarreras[i].getEstudiantes()[j].rut << ", " << "ponderado" << endl; 
      }
      salida.close();
    }
}