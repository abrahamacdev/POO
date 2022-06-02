CXX = g++
STD = c++11
CXXFLAGS = -std=$(STD)

P1_DIR = ../P1
OBJETOS =  luhn.o main.o cadena.o fecha.o articulo.o tarjeta.o usuario.o
CABECERA_CADENA = $(P1_DIR)/cadena.hpp

 # --------------- Ejecutables ---------------
all: clean-main main_exe

main_exe: main
	./$<

#main: $(OBJETOS)
#	$(CXX) $(CXXFLAGS) -o $@ $^ -lcrypt

main: main.o luhn.o cadena.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcrypt
# ---------------------------------------------

clave_fake.o: ../ClaveFake.h



# --------------- Objetos ---------------
main.o: main.cpp cadena.o
	$(CXX) $(CXXFLAGS) -c main.cpp

luhn.o: $(CABECERA_CADENA) ../luhn.cpp
	$(CXX) $(CXXFLAGS) -c ../luhn.cpp

cadena.o: $(CABECERA_CADENA) $(P1_DIR)/cadena.cpp
	$(CXX) $(CXXFLAGS) -c $(P1_DIR)/cadena.cpp

fecha.o: $(CABECERA_CADENA) $(P1_DIR)/fecha.hpp $(P1_DIR)/fecha.cpp
	$(CXX) $(CXXFLAGS) -c $(P1_DIR)/fecha.cpp

articulo.o: $(CABECERA_CADENA) $(P1_DIR)/fecha.hpp articulo.hpp articulo.cpp
	$(CXX) $(CXXFLAGS) -c articulo.cpp

tarjeta.o: $(CABECERA_CADENA) $(P1_DIR)/fecha.hpp usuario.hpp tarjeta.hpp tarjeta.cpp
	$(CXX) $(CXXFLAGS) -c tarjeta.cpp

usuario.o: $(CABECERA_CADENA) articulo.hpp tarjeta.hpp usuario.hpp usuario.cpp
	 $(CXX) $(CXXFLAGS) -c usuario.cpp
# ---------------------------------------------




# --------------- Limpieza ---------------
clean-main: clean
	rm -rf main

clean:
	rm -rf *.o core *~
# ---------------------------------------------