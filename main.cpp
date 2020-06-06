#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "omp.h"
#include <chrono>


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
vector<string> calcularPonderacion(int nem, int ranking, int matematicas, int lenguaje, int ciencias, int historia);
vector<int> obtenerPonderaciones(std::string linea);
vector<string> obtenerCarreras();
void foo(ifstream& in);
std::string lineaSoloRut(std::string linea);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */

int main(int argc, char** argv) {

    if(argc > 1){

        //abrir archivo de ponderaciones necesarias
        
        //control de tiempo de ejecucion, tiempo de inicio
        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float,std::milli> duration = end - start;


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

            if(entrada){    
#pragma omp parallel
            {
#pragma omp single
                {
                    for (std::string linea; getline(entrada, linea);) {
#pragma omp task
                        {
                            string rutaSalida = argv[3];
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
                                vector<string> fila;
                                fila = calcularPonderacion(nem, ranking, matematica, lenguaje, ciencias, historia);
                                rutaSalida = rutaSalida + fila[0] + ".txt";
                                std::ofstream salida(rutaSalida, fstream::app);
                                //cout << "inscrito el rut: " << rut << " en la carrera: " << fila.at(0) << endl;
                                //escribir el resultado
#pragma omp critical                                
                                salida << rut << ", " << fila.at(1) << std::endl;
                                salida.close();
                            }
                            puntajes.clear();
                        }                       
                    }
                }
            }
            }else{
                cout << "fallo al encontrar el archivo" << endl;
            }
            std::cout << duration.count() << "s" << std::endl;

        }
        else if(opcion == 2){

            /**
            Control de tiempo de ejecucion segundo proceso. NO FUNCIONAL
            auto start2 = std::chrono::system_clock::now();
            auto end2 = std::chrono::system_clock::now();
            std::chrono::duration<float,std::milli> duration2 = end2 - start2;
            */

            // Recepcion de rut
            int rut;
            rut = std::stoi(argv[2]);
            // Validacion de rut
            try{
                rut = std::atoi(argv[2]);
            }catch(std::invalid_argument const &e){
                cout << "Rut invalido " << argv[2] << endl;
            }

            //Lectura de archivos y validacion. Deberia poder abrir todos los archivos del folder
            //Temporalmente se utilizan directamente. El push_back luego será con obtenerCarreras[i]
            vector<string>rutas_archivos;
            string ruta = argv[3];
            rutas_archivos.push_back(ruta+"/21015.txt");
            rutas_archivos.push_back(ruta+"/21074.txt");

            // Se crea vector de ifstream. fstream no es copyable entonces se procede a
            // crear un vector con las posiciones de memoria de cada archivo
            vector<ifstream*> archivos_carreras;
            for(size_t i = 0; i < rutas_archivos.size(); i++){
                ifstream* in = new ifstream;
                archivos_carreras.push_back(in);
                archivos_carreras[i]->open(rutas_archivos.at(i));
            }
            foo(*archivos_carreras[1]);

            // Verificar que esten todos los archivos. Por ahora if(1)
            if(1){
                int num_linea;
                int encontrado = 0;
                // Recorrer cada archivo
                for (size_t i = 0; i<archivos_carreras.size();i++){
                    num_linea = 0;
                    // Se aplican los break para que el programa no siga buscando una vez encontrado
                    if(encontrado == 1){
                        break;
                    }
                    //Recorrer cada linea de cada archivo
                    for (std::string linea; getline(*archivos_carreras.at(i), linea);){
                        num_linea ++;
                        if(rut == std::stoi(lineaSoloRut(linea))){
                            cout << "El rut fue encontrado en el archivo "<< rutas_archivos.at(i)<<endl;
                            cout << "En la linea numero " << num_linea <<endl;
                            encontrado = 1;
                            break;
                        }
                    }
                }
                if(encontrado == 0){
                    cout << "El rut no existe en la base de datos" << endl;
                }
            }else{
                cout << "Uno o más archivos no existe";
            }
        }
        else{
            participantes();
        }

    }else{
        cout << "Debe ingresar informacion por consola" << endl;
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

vector<int> obtenerPonderaciones(std::string linea) {
    vector<int> arreglo;
    std::stringstream ss(linea);
    std::string item;

    while (std::getline(ss, item, ',')) {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
    }

    return arreglo;
}

void foo(ifstream& in){

}

std::string lineaSoloRut(std::string linea){
    std::string soloRut;
    int pos = linea.find(",");
    soloRut = linea.substr(0,pos);
    return soloRut;
}


/**
 * Estructura archivo admision
 * Codigo carrera
 * NEM
 * Ranking
 * Lenguaje
 * Matematicas
 * Historia o ciencias
 * Minimo postulación PSU
 * Vacantes
 * Primer matriculado 2019
 * Ultimo matriculado 2019 
 */

// Esta funcion se utilizara para contener el nombre de todos los archivos. [carrera1,carrera2,...]
vector<string> obtenerCarreras(){
    std::string texto;
    vector<string> salidaMala;
    salidaMala.push_back("NULL");
    salidaMala.push_back("NULL");
    std::ifstream admision;
    admision.open("data/admision.csv", fstream::in); 

    if(admision){
        vector<string> salida;
        while(std::getline(admision, texto)){
            vector<int> valores;
            valores = obtenerPonderaciones(texto);
            salida.push_back(std::to_string(valores.at(0)));
        }
        return salida;
    }
    else{
        cout << "Falta archivo de admision o formato incorrecto" << endl;
        admision.close();
        return salidaMala;
    }

}



vector<string> calcularPonderacion(int nem, int ranking, int matematicas, int lenguaje, int ciencias, int historia){
    //retorna como primer valor el {codigo carrera} y segundo valor {rut, ponderacion}
    std::string texto;
    vector<string> salidaMala;
    salidaMala.push_back("NULL");
    salidaMala.push_back("NULL");
    std::ifstream admision;
    admision.open("data/admision.csv", fstream::in); 

    if(admision){
        while(std::getline(admision, texto)){
            vector<string> salida;

            vector<int> valores;
            valores = obtenerPonderaciones(texto);
            if(valores.size() >= 9){
                float ponderacion;
                float pnem = (float) valores.at(1)/100;
                float prank = (float) valores.at(2)/100;
                float pleng = (float) valores.at(3)/100;
                float pmat = (float) valores.at(4)/100;
                float phoc = (float) valores.at(5)/100;
                float pprimer = valores.at(8);
                float pultimo = valores.at(9);
                //cout << valores.at(0) << ", " << valores.at(1) << ", " << valores.at(2) << ", " << valores.at(3) << ", " << valores.at(4) << ", " << valores.at(5) << ", " << valores.at(6) << ", " << valores.at(7) << ", " << valores.at(8) << ", " << valores.at(9) << ", " << endl;

                ponderacion = nem*pnem + ranking* prank + matematicas*pmat + lenguaje * pleng;
                if(ciencias != 0 && historia == 0){
                    ponderacion += ciencias*(float)(phoc);
                }
                else if(ciencias == 0 && historia != 0){
                    ponderacion += historia*phoc;
                }
                else if(ciencias != 0 && historia != 0 && ciencias > historia) {
                    ponderacion += ciencias*phoc;
                }
                else if(ciencias != 0 && historia != 0 && historia > ciencias){
                    ponderacion += historia*phoc;
                }
                if(ponderacion > pultimo && ponderacion < pprimer && ponderacion > valores.at(6)){
                    salida.push_back(std::to_string(valores.at(0)));
                    salida.push_back(std::to_string(ponderacion));
                    admision.close();
                    //cout << "inscribio a NEM: " << nem << " en la carrera: " << salida.at(0) << " con la ponderacion: " << salida.at(1) << endl;
                    return salida;  
                }
                else{
                    //cout << "carrera: " << valores.at(0) << " , " << ponderacion << "para el NEM: " << nem << " fallo al escribir esto" << endl;
                    //cout << ponderacion << endl;
                }
            }
            else{
                cout << "mal formateado el archivo de admision" << endl;
            }
        }
    }
    else{
        cout << "falta archivo de admision o formato no correcto || O NO SE ABRIO LA WEA" << endl;
        admision.close();
        return salidaMala;
    }
    admision.close();
    return salidaMala;
}

/**
 * 
 * se necesita ordenar el archivo admision para dejar las carreras con mayor demanda primero
 * carreras con mayor cupo, carreras con el puntaje minimo del año anterior más alto
 * 
 */