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
#define iteraciones 5000

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
vector<EstudianteCarrera> clasificarEstudiantes(string, map<int, Carrera> &);
void escribirCarreras(vector<EstudianteCarrera> listaCarreras, string rutaSalida);

int main(int argc, char **argv)
{
  auto start = chrono::system_clock::now();

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
          map<int, Carrera> carreras = generarCarreras(rutaAdmisionCsv);
          vector<EstudianteCarrera> carrerasLlenas = clasificarEstudiantes(rutaPuntajesCsv, carreras);
          escribirCarreras(carrerasLlenas, rutaSalida);
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
      string ruta;
      
      try
      {
        rut = atoi(argv[2]);
      }
      catch (invalid_argument const &e)
      {
        cout << "El RUT " << argv[2] << " no es válido " << endl;
      }

      try
      {
        ruta = argv[3];
      }
      catch (invalid_argument const &e)
      {
        cout << "La ruta " << argv[2] << " no es válida" <<endl;
      }

       vector<string> rutasArchivos;
        map<int, Carrera> carreras = generarCarreras(rutaAdmisionCsv);

        for (auto const& x : carreras)
        {
          string rutaCompleta = ruta + "/" + std::to_string(x.second.codigo) + + ".txt";
          rutasArchivos.push_back(rutaCompleta);
        }

        pair<int, string> archivo = buscarRut(rutasArchivos, to_string(rut));
        if (archivo.first <= 0) {
          cout << "No se encontró el RUT " << rut << " en ninguno de los archivos de la ruta " << ruta << endl;
        } else {
        cout << "RUT " << rut << " encontrado en el archivo " << archivo.second << " en la linea " << archivo.first << endl;
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
  auto end = chrono::system_clock::now();
  chrono::duration<float, milli> duration = end - start;

  cout << duration.count() << "'ms" << endl;
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
  cout << "Sebastián Albornoz" << endl;
  cout << "Sebastián Santelices" << endl;
  cout << "Jorge Verdugo" << endl;
}

void imprimirCarreras(vector<Carrera> carreras)
{
  for (long unsigned int i = 0; i < carreras.size(); i++)
  {
    Carrera carrera = carreras[i];
    cout << carrera.getCodigo() << endl;
  }
}

vector<EstudianteCarrera> clasificarEstudiantes(string rutaCsv, map<int, Carrera> &carreras)
{
  map<long, Estudiante> estudiantesAsignados;
  vector<EstudianteCarrera> estudiantesCarreras;
  vector<EstudianteCarrera> estudiantesSeleccionados;

  ifstream input(rutaCsv);
  int i = 0;

  for (string linea; getline(input, linea) && i < iteraciones; i++)
  {
    Estudiante estudiante = Estudiante(linea);
    for (auto const &c : carreras)
    {

      Carrera carrera = c.second;
      float ponderado = carrera.valorPonderado(estudiante);
      estudiantesCarreras.push_back(EstudianteCarrera(estudiante, carrera, ponderado));
    }
  }

  ordenarRecursivo(estudiantesCarreras, 0, estudiantesCarreras.size());

  long unsigned int j = 0;
  while (quedanVacantesDisponibles(carreras) && j < estudiantesCarreras.size())
  {
    EstudianteCarrera estudianteCarrera = estudiantesCarreras[j];
    Estudiante estudiante = estudianteCarrera.estudiante;
    Carrera carrera = estudianteCarrera.carrera;
    if (estudiantesAsignados.find(estudiante.rut) == estudiantesAsignados.end())
    {
      // Si aún no se asigna el usuario
      bool seAgrego = carreras[carrera.codigo].agregarEstudiante(estudiante);
      if (seAgrego)
      {
        cout << "Se asignó al estudiante " << estudiante.rut << " a la carrera " << carrera.codigo << " con " << estudianteCarrera.ponderado << " puntos ponderados" << endl;
        estudiantesAsignados.insert(pair<long, Estudiante>(estudiante.rut, estudiante));
        //agregar a lista nueva
        estudiantesSeleccionados.push_back(estudianteCarrera);
      }
    }

    j++;
  }
  return estudiantesSeleccionados;
}

bool quedanVacantesDisponibles(map<int, Carrera> carreras)
{
  for (auto const &c : carreras)
  {
    Carrera carrera = c.second;
    if (!carrera.estaLlena())
    {
      return true;
    }
  }
  return false;
}

void escribirCarreras(vector<EstudianteCarrera> carreras, string rutaSalida)
{
  for (long unsigned int i = 0; i < carreras.size(); i++)
  {
    string nombreArchivo = rutaSalida + std::to_string(carreras[i].carrera.codigo) + ".txt";
    ofstream salida(nombreArchivo, fstream::app);
    salida << carreras[i].estudiante.rut << ", " << carreras[i].ponderado << endl;
  }
}