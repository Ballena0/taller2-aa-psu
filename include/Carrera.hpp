#ifndef __CARRERA_H__
#define __CARRERA_H__

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Estudiante.hpp"

using namespace std;

class Carrera {
	private:
		vector<Estudiante> estudiantes;
	public:
		int codigo;
		int nem;
		int ranking;
		int lenguaje;
		int matematica;
		int ciencias;
		int promedioMinimo;
		int vacantes;
		float primero;
		float ultimo;
		Carrera(string);
		Carrera(int, int, int, int, int, int, int, int, float, float);
		~Carrera();
		bool operator <= (const Carrera&) const;
		bool operator >= (const Carrera&) const;
		
		bool agregarEstudiante(Estudiante);
		static void ordenarRecursivo(vector<Carrera> &, int, int);
		int getCodigo();
		float valorPonderado(Estudiante);
		vector<Estudiante> getEstudiantes();
};

#endif // __CARRERA_H__