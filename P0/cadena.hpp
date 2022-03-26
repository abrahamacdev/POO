//
// Created by Judith Olalde Alonso on 6/3/22.
//

//
// Created by abrah on 26/02/2022.
//

#ifndef FECHA_CADENA_HPP
#define FECHA_CADENA_HPP

#include "cstring"
#include "vector"
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "iostream"


class Cadena {

    char* s_;
    unsigned int tam_;

public:

    // Constructores
    Cadena();
    Cadena(unsigned int tamanio, const char relleno);
    explicit Cadena(unsigned int tamanio);
    Cadena(const Cadena& c);
    Cadena(const char* a);

    // Observadores
    unsigned int length() const { return tam_; };
    const char& at(size_t i) const;
    char& at(size_t i);
    Cadena substr(unsigned int indx, unsigned int tam);
    Cadena substr(unsigned int indx, unsigned int tam) const;

    // Conversores
    operator const char * ();
    operator const char * () const;

    // Operadores
    Cadena& operator =(const Cadena& c2);
    Cadena& operator =(const char* c2);
    Cadena& operator +=(const Cadena& c2);
    Cadena operator +(const Cadena& c2);
    Cadena operator +(const Cadena& c2) const;
    bool operator ==(const Cadena& c2);
    bool operator <(const Cadena& c2);
    bool operator <=(const Cadena& c2);
    bool operator >(const Cadena& c2);
    bool operator >=(const Cadena& c2);
    bool operator !=(const Cadena& c2);
    char& operator[](unsigned int i);
    const char& operator[](unsigned int i) const;


    ~Cadena();

    class Utilidades {

    public:

        static Cadena vector2Cadena(std::vector<char>& v);
        static Cadena numero2Cadena(int n);
    };

private:
    void eliminar();
};

#endif //FECHA_CADENA_HPP