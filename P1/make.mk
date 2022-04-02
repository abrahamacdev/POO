CXX = g++
STD = c++11
CXXFLAGS = -std=$(STD) -g -Wall -pedantic
CPPFLAGS = -DP1 -I../Tests-auto -I.
LDFLAGS = -I$(TESTS_DIR)
VPATH = ../Tests-auto:.

TESTS_DIR = ../Tests-auto/
EJECUTABLES = test-P1-auto testfechacadena-consola

all: $(EJECUTABLES)

# Crea el ejecutable para el test por consola
testfechacadena-consola: fecha.o cadena.o test-fechacadena-consola.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compila el código fuente del test por consola
test-fechacadena-consola.o: test-fechacadena-consola.cpp fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./test-fechacadena-consola.cpp

# Crea el ejecutable de los tests automáticos
test-P1-auto: test-caso0-cadena-auto.o test-caso0-fecha-auto.o test-auto.o cadena.o fecha.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Compila el código fuente del test automático
test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp
#$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TESTS_DIR)test-caso0-fecha-auto.cpp $(TESTS_DIR)test-caso0-cadena-auto.cpp $(TESTS_DIR)test-auto.cpp

# Compilación de la clase fecha
fecha.o: fecha.hpp cadena.hpp
	$(CXX) $(CXXFLAGS) -c fecha.cpp

# Compilación de la clase cadena
cadena.o: cadena.hpp
	$(CXX) $(CXXFLAGS) -c cadena.cpp

clean:
	rm -rf *.o core *~ $(EJECUTABLES)