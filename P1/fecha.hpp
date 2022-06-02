//
// Created by abrah on 22/02/2022.
//

#ifndef FECHA_FECHA_HPP
#define FECHA_FECHA_HPP

#include <climits>
#include "ctime"
#include "iostream"

#include "cadena.hpp"

class Fecha {

public:

    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    // Contructores
    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const char* f);

    // Auxiliares
    void imprimir() const noexcept;

    // Observadores
    inline int dia() const noexcept { return dia_; }
    inline int mes() const noexcept { return mes_; }
    inline int anno() const noexcept { return anio_; }
    const char* cadena() const noexcept;

    // Operadores
    Fecha operator +(int d) const;
    Fecha operator -(int d) const;
    Fecha& operator +=(int d);
    Fecha& operator -=(int d);
    Fecha operator ++(int d);        // Postfijo (f++ -> postincremento) {Devolvemos copia y sumamos}
    Fecha operator --(int d);        // Postfijo (f-- -> postdecremento) {Devolvemos copia y restamos}
    Fecha& operator ++();            // Prefijo (++f -> preincremento) {Sumamos y devolvemos el mismo}
    Fecha& operator --();            // Prefijo (--f -> predecremento) {Sumamos y devolvemos el mismo}


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

    int dia_, mes_, anio_;

    // Auxiliar
    static bool diaValido(int d, int m, int y = Utilidades::anioActual());
    static bool mesValido(int m);
    static bool anioValido(int a);
    void validar();
    Cadena dia2Cadena() const;
    Cadena anio2Cadena() const;
};

bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);

std::ostream& operator << (std::ostream& s, const Fecha& f);      // Operación de extracción
std::istream& operator >> (std::istream& s, Fecha& f);            // Operación de insercción

#endif //FECHA_FECHA_HPP
