CXX = g++
CXXFLAGS = -std=c++11 #-g -Wall -pedantic
CPPFLAGS = -DP0 -I../Tests-auto -I.
VPATH = ../Tests-auto/

all: test-P0-auto testfechacadena-consola clean

# Crea el ejecutable para el test por consola
testfechacadena-consola: fecha.o cadena.o test-fechacadena-consola.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

# Compila el código fuente del test por consola
test-fechacadena-consola.o: test-fechacadena-consola.cpp fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./test-fechacadena-consola.cpp

# Crea el ejecutable de los tests automáticos
test-P0-auto: test-caso0-cadena-auto.o test-caso0-fecha-auto.o test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $^

# Individual de fecha
#test-caso0-fecha-auto.o: test-auto.hpp fecha.hpp cadena.hpp
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(VPATH)test-caso0-fecha-auto.cpp

# Individual de cadena
#test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(VPATH)test-caso0-cadena-auto.cpp

# Original con toodo
test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: test-auto.hpp fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(VPATH)test-caso0-fecha-auto.cpp $(VPATH)test-caso0-cadena-auto.cpp $(VPATH)test-auto.cpp

fecha.o: fecha.hpp cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c fecha.cpp

cadena.o: cadena.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cadena.cpp

clean:
	rm -rf *.o core *~