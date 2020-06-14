#include "../include/EstudianteCarrera.hpp"


EstudianteCarrera::EstudianteCarrera(Estudiante _estudiante, Carrera _carrera, float _ponderado) {
    estudiante = _estudiante;
    carrera = _carrera;
    ponderado = _ponderado;
}

EstudianteCarrera::~EstudianteCarrera()
{

}

bool EstudianteCarrera::operator >= (const EstudianteCarrera &eC) const {
    if (ponderado == eC.ponderado) {
        if (carrera.codigo == eC.carrera.codigo) {
            return true;
            
        }
        return carrera > eC.carrera;
    }
    return ponderado > eC.ponderado;
}

bool EstudianteCarrera::operator <= (const EstudianteCarrera &eC) const {
    if (ponderado == eC.ponderado) {
        if (carrera.codigo == eC.carrera.codigo) {
            return true;
            
        }
        return carrera < eC.carrera;
    }
    return ponderado < eC.ponderado;
}