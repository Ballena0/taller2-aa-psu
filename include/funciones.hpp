#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <chrono>
#include <algorithm>

#include "omp.h"

#include "Carrera.hpp"

using namespace std;

void participantes();
bool existeArchivo(string);

vector<string> split(string, char);
vector<Carrera> generarCarreras(string);
vector<Carrera> clasificarEstudiantes(string, vector<Carrera>);
void ordenarRecursivo(vector<pair<int, float>> &, int, int);