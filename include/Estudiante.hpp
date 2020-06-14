#ifndef __ESTUDIANTE_H__
#define __ESTUDIANTE_H__

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class Estudiante {
	private:
		
	public:
		long rut;
		int nem;
		int ranking;
		int matematica;
		int lenguaje;
		int ciencias;
		int historia;
		Estudiante();
		Estudiante(long, int, int, int, int, int, int);
		Estudiante(string);
		~Estudiante();

};

#endif // __ESTUDIANTE_H__