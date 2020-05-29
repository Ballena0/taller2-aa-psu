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
void participantes();

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
        int opcion;
        try{
            opcion = std::atoi(argv[1]);
        }
        catch(std::invalid_argument const &e){ 
            cout << "No existe la accion " << argv[1] << endl;
        }

        if(opcion == 1){
            //generar archivos

            string rutaPuntajes = argv[2];
            std::ifstream entrada(rutaPuntajes);
            cout << rutaPuntajes << endl;
            string rutaSalida = argv[3];
            std::ofstream salida(rutaSalida);
            cout << rutaSalida << endl;
            if(entrada && salida){
#pragma omp parallel
            {
#pragma omp single
                {
                    for (std::string linea; getline(entrada, linea);) {
#pragma omp task
                        {
                            vector<int> puntajes = obtenerPuntajes(linea);
                            if(puntajes.size() >= 6) {
                                int rut = puntajes.at(0);
                                int nem = puntajes.at(1);
                                int ranking = puntajes.at(2);
                                int matematica = puntajes.at(3);
                                int lenguaje = puntajes.at(4);
                                int ciencias = puntajes.at(5);
                                int historia = puntajes.at(6);

                                //calculo de porcentajes para cada carrera
                                int ponderado;
                                std::string fila;
                                fila = std::to_string(rut) + ";" + to_string(ponderado);
                                
                                //escribir el resultado
#pragma omp critical                                
                                salida << fila << std::endl;
                            }
                        }                        
                    }
                }

            }
            salida.close();
            }else{
                cout << "fallo al encontrar el archivo" << endl;
            }

        }
        else if(opcion == 2){
            //busqueda de rut

            int rut;
            string ruta = argv[3];
            std::ifstream archivos(ruta);
            try{
                rut = std::atoi(argv[2]);
            }catch(std::invalid_argument const &e){
                cout << "rut invalido " << argv[2] << endl;
            }

            if(archivos){
                //codigo
            }else{
                participantes();
            }
        }
        else{
            participantes();
        }

    }else{
        participantes();
    }
    return EXIT_SUCCESS;
}

void participantes() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Sebastián Albornoz" << std::endl;
    std::cout << std::endl << "Sebastián Santelices" << std::endl;
    std::cout << std::endl << "Jorge Verdugo" << std::endl;
}

vector<int> obtenerPuntajes(std::string linea) {
    vector<int> arreglo;
    std::stringstream ss(linea);
    std::string item;

    while (std::getline(ss, item, ';')) {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
    }

    return arreglo;
}   