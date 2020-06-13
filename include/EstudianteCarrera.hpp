#ifndef __ESTUDIANTECARRERA_H__
#define __ESTUDIANTECARRERA_H__

#include "Carrera.hpp"
#include "Estudiante.hpp"

class EstudianteCarrera {
	private:

	public:
		Estudiante estudiante;
		Carrera carrera;
		float ponderado;
		bool operator <= (const EstudianteCarrera&) const;
		bool operator >= (const EstudianteCarrera&) const;
		EstudianteCarrera(Estudiante, Carrera, float);
		~EstudianteCarrera();

};

#endif // __ESTUDIANTECARRERA_H__