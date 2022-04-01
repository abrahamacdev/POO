CXX = g++
CXXFLAGS = -std=c++11 #-g -Wall -pedantic
CPPFLAGS = -DP0 -I../Tests-auto -I.
VPATH = ../Tests-auto:.

TESTS_DIR = ../Tests-auto/
EJECUTABLES = test-P0-auto testfechacadena-consola

all: $(EJECUTABLES)

# Crea el ejecutable para el test por consola
testfechacadena-consola: fecha.o cadena.o test-fechacadena-consola.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

# Compila el código fuente del test por consola
test-fechacadena-consola.o: test-fechacadena-consola.cpp fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./test-fechacadena-consola.cpp

# Crea el ejecutable de los tests automáticos
test-P0-auto: test-caso0-cadena-auto.o test-caso0-fecha-auto.o test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $^

# Compila el código fuente del test automático
test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: test-auto.hpp fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TESTS_DIR)test-caso0-fecha-auto.cpp $(TESTS_DIR)test-caso0-cadena-auto.cpp $(TESTS_DIR)test-auto.cpp

# Compilación de la clase fecha
fecha.o: fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c fecha.cpp

# Compilación de la clase cadena
cadena.o: cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cadena.cpp

clean:
	rm -rf *.o core *~ $(EJECUTABLES)