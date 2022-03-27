//
// Created by abrah on 22/02/2022.
//

#ifndef FECHA_FECHA_HPP
#define FECHA_FECHA_HPP

#include <climits>
#include "ctime"
#include "stdio.h"
#include "cstring"
#include "vector"
#include "cadena.hpp"

using namespace std;

class Fecha {

    int dia_, mes_, anio_;

public:

    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    // Contructores
    Fecha();
    //Fecha(const Fecha& f);
    explicit Fecha(int d);
    Fecha(int d, int m);
    Fecha(int d, int m, int a);
    Fecha(const char* f);

    // Auxiliares
    void imprimir() const;

    // Observadores
    int dia() const;
    int mes() const;
    int anno() const;

    // Operadores
    Fecha operator +(int d);
    Fecha operator +(int d) const;
    Fecha operator -(int d);
    Fecha operator -(int d) const;
    Fecha& operator +=(int d);
    Fecha& operator -=(int d);
    Fecha operator ++(int d);        // Postfijo (f++ -> postincremento) {Devolvemos copia y sumamos}
    Fecha operator --(int d);        // Postfijo (f-- -> postdecremento) {Devolvemos copia y restamos}
    Fecha& operator ++();            // Prefijo (++f -> preincremento) {Sumamos y devolvemos el mismo}
    Fecha& operator --();            // Prefijo (--f -> predecremento) {Sumamos y devolvemos el mismo}
    bool operator==(const Fecha& f2) const;
    bool operator<(const Fecha& f2) const;
    bool operator>(const Fecha& f2) const;
    bool operator<=(const Fecha& f2) const;
    bool operator>=(const Fecha& f2) const;
    bool operator!=(const Fecha& f2) const;

    // Conversores
    operator const char * ();
    operator const char * () const;

    // Errores
    class Invalida: public std::exception{

        const char* porque;

    public:

        Invalida();
        explicit Invalida(const char* p);

        const char* por_que() const;
        const char *what() const throw() override;
    };

    class Utilidades {

    public:
        static int diaActual();

        static int mesActual();

        static int anioActual();

        static int maxDiaDelMes(int m, int y = anioActual());

        static const char* mes2Texto(int m);

        static const char* diaSemana2Texto(const Fecha& f);
    };

private:

    // Auxiliar
    static bool diaValido(int d, int m, int y = Utilidades::anioActual());
    static bool mesValido(int m);
    static bool anioValido(int a);
    vector<vector<char>> transformarFechaCadena(const char* f);
    Cadena dia2Cadena() const;
    Cadena anio2Cadena() const;
};

#endif //FECHA_FECHA_HPP
