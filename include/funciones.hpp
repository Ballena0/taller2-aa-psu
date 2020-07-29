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
map<int, Carrera> generarCarreras(string);
pair<int, string> buscarRut(vector<string>, string);
vector<Carrera> clasificarEstudiantes(string, vector<Carrera>);


// No mover las funciones de abajo, las funciones template solo puede alojarse en el archivo header
template <class T>
int obtenerIndicePivote(vector<T> &arr, int low, int high) {
	T pivote = arr[high];
	int i = (low - 1);

#pragma omp parallel for num_threads(4)
	for (int j = low; j <= high- 1; j++) {
		if (arr[j] >= pivote) {
			i++;
			swap(arr[i], arr[j]);
		} 
	} 
    swap(arr[i + 1], arr[high]);
	return (i + 1); 
} 

template <class T>
void ordenarRecursivo(vector<T> &arr, int low, int high) {
	if (low < high) { 

		int piv = obtenerIndicePivote(arr, low, high); 
#pragma omp parallel sections 
	{
#pragma omp section	
			ordenarRecursivo(arr, low, piv - 1); 	
#pragma omp section	
			ordenarRecursivo(arr, piv + 1, high);
		}		
		 
	}
		 
}

template <class T>
void swap(vector<T> &v, int x, int y) {
    T temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}