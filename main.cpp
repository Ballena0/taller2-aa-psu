#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "omp.h"


using namespace std;

/**
 * Función que muestra los participantes del grupo
 */
void participante();

/**
 * 
 * @param linea Línea leída desde un archivo
 * @return el arreglo con los puntajes
 */
vector<int> obtenerPuntajes(std::string linea);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */

int main(int argc, char** argv) {
    if(argc > 1){
        // hace algo
    }else{
        participante();
    }
    return EXIT_SUCCESS;
}

void participante() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Sebastián Albornoz" << std::endl;
    std::cout << std::endl << "Sebastián Santelices" << std::endl;
    std::cout << std::endl << "Jorve Verdugo" << std::endl;
}