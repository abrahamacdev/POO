CXX = g++
STD = c++11
CXXFLAGS = -std=$(STD)

P1_DIR = ../P1
OBJETOS = main.o cadena.o fecha.o articulo.o clave.o numero.o tarjeta.o usuario.o
CABECERA_CADENA = $(P1_DIR)/cadena.hpp

 # --------------- Ejecutables ---------------
all: clean-main main

main: $(OBJETOS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcrypt
# ---------------------------------------------




# --------------- Objetos ---------------
main.o: main.cpp clave.hpp usuario.hpp articulo.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

cadena.o: $(CABECERA_CADENA) $(P1_DIR)/cadena.cpp
	$(CXX) $(CXXFLAGS) -c $(P1_DIR)/cadena.cpp

fecha.o: $(CABECERA_CADENA) $(P1_DIR)/fecha.hpp $(P1_DIR)/fecha.cpp
	$(CXX) $(CXXFLAGS) -c $(P1_DIR)/fecha.cpp

articulo.o: $(CABECERA_CADENA) $(P1_DIR)/fecha.hpp articulo.hpp articulo.cpp
	$(CXX) $(CXXFLAGS) -c articulo.cpp

clave.o: $(CABECERA_CADENA) clave.hpp clave.cpp
	$(CXX) $(CXXFLAGS) -c clave.cpp

numero.o: $(CABECERA_CADENA) ../luhn.cpp numero.hpp numero.cpp
	$(CXX) $(CXXFLAGS) -c numero.cpp

tarjeta.o: $(P1_DIR)/fecha.hpp numero.hpp usuario.hpp tarjeta.hpp tarjeta.cpp
	$(CXX) $(CXXFLAGS) -c tarjeta.cpp

usuario.o: $(CABECERA_CADENA) articulo.hpp tarjeta.hpp numero.hpp clave.hpp usuario.hpp usuario.cpp
	 $(CXX) $(CXXFLAGS) -c usuario.cpp
# ---------------------------------------------




# --------------- Limpieza ---------------
clean-main: clean
	rm -rf main

clean:
	rm -rf *.o core *~
# ---------------------------------------------