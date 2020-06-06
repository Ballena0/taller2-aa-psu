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
