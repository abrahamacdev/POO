CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -pedantic
CABECERAS = fecha.hpp cadena.hpp
FUENTES = test-fechacadena-consola.cpp
OBJETOS = test-fechacadena-consola.o main.o


CPPFLAGS = -DP0 -I../Tests-auto -I
VPATH = ../Tests-auto:.

all: programa

programa: clean main.o
	$(CXX) -o programa main.o

main.o: main.cpp fecha.hpp cadena.hpp
	$(CXX) -c main.cpp

#programa: clean $(OBJETOS)
	#$(CXX) -o $@ $(CXXFLAGS) $(OBJETOS) $(CABECERAS)

test-fechacadena-consola.o: $(CABECERAS) $(FUENTES)
	$(CXX) $(CPPFLAGS) -c $a $(CXXFLAGS) $(FUENTES)

clean:
	$(RM) programa core *~ $(OBJETOS)