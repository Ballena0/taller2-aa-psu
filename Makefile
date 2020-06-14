CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -fopenmp
MKDIR = mkdir -p

LIBS = -lm

directorios:
	$(MKDIR) build dist

Estudiante.o: directorios src/Estudiante.cpp include/Estudiante.hpp
	$(CXX) $(CXXFLAGS) -c src/Estudiante.cpp -o build/Estudiante.o

Carrera.o: directorios src/Carrera.cpp include/Carrera.hpp
	$(CXX) $(CXXFLAGS) -c src/Carrera.cpp -o build/Carrera.o

EstudianteCarrera.o: directorios src/EstudianteCarrera.cpp include/EstudianteCarrera.hpp
	$(CXX) $(CXXFLAGS) -c src/EstudianteCarrera.cpp -o build/EstudianteCarrera.o

funciones.o: directorios src/funciones.cpp include/funciones.hpp
	$(CXX) $(CXXFLAGS) -c src/funciones.cpp -o build/funciones.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o Estudiante.o Carrera.o funciones.o EstudianteCarrera.o
	$(CXX) $(CXXFLAGS) -o dist/promediador-omp build/main.o build/Estudiante.o build/Carrera.o build/EstudianteCarrera.o build/funciones.o $(LIBS) 
	rm -fr build

clean:
	rm -fr *.o a.out core promediador-omp dist build 

.DEFAULT_GOAL := all
