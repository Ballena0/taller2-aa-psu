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

#define numeroEstudiantes 5015751
#define rutaAdmisionCsv "data/admision.csv"

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */

void participantes();
bool existeArchivo(string);
vector<Carrera> generarCarreras(string);
vector<Carrera> clasificarEstudiantes(string, vector<Carrera>);
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
        if (existeArchivo(rutaPuntajesCsv))
        {
          cout << "Entro a ambos" << endl;
          vector<Carrera> carreras = generarCarreras(rutaAdmisionCsv);
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

void participantes()
{
  cout << endl
       << "=== PRUEBA 2 ===" << endl;
  cout << endl
       << "Sebastián Albornoz" << endl;
  cout << endl
       << "Sebastián Santelices" << endl;
  cout << endl
       << "Jorge Verdugo" << endl;
}

vector<Carrera> generarCarreras(string rutaCsv)
{
  vector<Carrera> carreras;

  ifstream entrada(rutaCsv);
  for (string linea; getline(entrada, linea);)
  {
    Carrera carrera = Carrera(linea);
    carreras.push_back(carrera);
  }

  return carreras;
}

vector<Carrera> clasificarEstudiantes(string rutaCsv, vector<Carrera> carreras)
{
  vector<Carrera> carreraLlenas;

  cout << "uwu" << endl;

  ifstream input(rutaCsv);
#pragma omp parallel
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
  }

  return carreraLlenas;
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
