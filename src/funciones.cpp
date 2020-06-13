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

int obtenerIndicePivote(vector<pair<int, float>> &arr, int low, int high) {
	pair<int, float> pivote = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++) {
		if (arr[j].second >= pivote.second) {
			i++;
			swap(arr[i], arr[j]);
		} 
	} 
    swap(arr[i + 1], arr[high]);
	return (i + 1); 
} 

void ordenarRecursivo(vector<pair<int, float>> &arr, int low, int high) {
	if (low < high) { 
		int piv = obtenerIndicePivote(arr, low, high); 

		ordenarRecursivo(arr, low, piv - 1); 
		ordenarRecursivo(arr, piv + 1, high); 
	} 
}

void swap(vector<pair<int, float>> &v, int x, int y) {
    pair<int, float> temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}
