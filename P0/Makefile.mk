CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -pedantic
CABECERAS = fecha.hpp cadena.hpp
FUENTES = test-fechacadena-consola.cpp
OBJETOS = test-fechacadena-consola.o
NOMBRE_EJECUTABLE = programa

CPPFLAGS = -DP0 -I../Tests-auto -I
VPATH = ../Tests-auto:.



all: programa

programa: clean $(OBJETOS)
	$(CXX) -o $(NOMBRE_EJECUTABLE) $(OBJETOS)

test-fechacadena-consola.o: $(CABECERAS) $(FUENTES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(FUENTES)

clean:
	$(RM) programa core *~ $(OBJETOS) $(NOMBRE_EJECUTABLE)