CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

OBJETOS = Cadena.hpp

all: programa

programa: $(OBJETOS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJETOS)

clean:
	$(RM) programa $(OBJETOS) core *~