CXX = g++
STD = c++11
CXXFLAGS = -std=$(STD)

P1_DIR = ../P1

all: clean-main main

main: main.o cadena.o clave.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcrypt

cadena.o: $(P1_DIR)/cadena.hpp $(P1_DIR)/cadena.cpp
	$(CXX) $(CXXFLAGS) -c $(P1_DIR)/cadena.cpp

clave.o: $(P1_DIR)/cadena.hpp clave.hpp clave.cpp
	$(CXX) $(CXXFLAGS) -c clave.cpp

main.o: main.cpp clave.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean-main: clean
	rm -rf main

clean:
	rm -rf *.o core *~