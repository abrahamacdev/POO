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
    Cadena enTexto;

    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

public:

    // Contructores
    Fecha();
    explicit Fecha(int d);
    Fecha(int d, int m);
    Fecha(int d, int m, int a);
    Fecha(const char* f);

    // Auxiliares
    void imprimir();

    // Observadores
    int dia() const;
    int mes() const;
    int anno() const;

    // Operadores
    Fecha operator +(int d);
    Fecha operator -(int d);
    Fecha& operator +=(int d);
    Fecha& operator -=(int d);
    Fecha operator ++(int d);        // Postfijo (f++ -> postincremento) {Devolvemos copia y sumamos}
    Fecha operator --(int d);        // Postfijo (f-- -> postdecremento) {Devolvemos copia y restamos}
    Fecha operator ++();            // Prefijo (++f -> preincremento) {Sumamos y devolvemos el mismo}
    Fecha operator --();            // Prefijo (--f -> predecremento) {Sumamos y devolvemos el mismo}
    bool operator==(const Fecha& f2) const;
    bool operator<(const Fecha& f2) const;
    bool operator>(const Fecha& f2) const;
    bool operator<=(const Fecha& f2) const;
    bool operator>=(const Fecha& f2) const;
    bool operator!=(const Fecha& f2) const;

    // Conversores
    operator const char * ();

    // Errores
    class Invalida: public std::exception{

        const char* porque;

    public:

        Invalida(): porque("Ni idea"){};
        Invalida(const char* p): porque(p){};

        const char* por_que() const{
            return porque;
        }
    };

    class Utilidades {

    public:
        static int diaActual(){
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mday;
        }

        static int mesActual(){
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mon + 1;
        }

        static int anioActual(){
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_year + 1900;
        }

        static int maxDiaDelMes(int m, int y = anioActual()){
            if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
                return 31;
            else if(m == 4 || m == 6 || m == 9 || m == 11)
                return 30;
            else {
                if(y % 4 == 0) {
                    if(y % 100 == 0) {
                        if(y % 400 == 0)
                            return 29;
                        return 28;
                    }
                    return 29;
                }
                return 28;
            }
        }

        static const char* mes2Texto(int m){
            switch (m) {
                case 1:
                    return "enero";
                case 2:
                    return "febrero";
                case 3:
                    return "marzo";
                case 4:
                    return "abril";
                case 5:
                    return "mayo";
                case 6:
                    return "junio";
                case 7:
                    return "julio";
                case 8:
                    return "agosto";
                case 9:
                    return "septiembre";
                case 10:
                    return "octubre";
                case 11:
                    return "noviembre";
                case 12:
                    return "diciembre";
                default:
                    return "";
            }
        }

        static const char* diaSemana2Texto(const Fecha& f){
            struct tm expire_time = {};
            expire_time.tm_year = f.anio_ - 1900;
            expire_time.tm_mon = f.mes_ - 1;
            expire_time.tm_mday = f.dia_;

            time_t tempTime = mktime(&expire_time);
            const std::tm * time_out = std::localtime(&tempTime);

            int diaSemana = time_out->tm_wday;

            switch (diaSemana) {
                case 0:
                case 7:
                    return "domingo";

                case 1:
                    return "lunes";

                case 2:
                    return "martes";

                case 3:
                    return "miércoles";

                case 4:
                    return "jueves";

                case 5:
                    return "viernes";

                case 6:
                    return "sábado";

                default:
                    return "";
            }
        }
    };

private:

    // Auxiliar
    bool diaValido(int d, int m);
    bool mesValido(int m);
    bool anioValido(int a);
    vector<vector<char>> transformarFechaCadena(const char* f);
    Cadena dia2Cadena();
    Cadena mes2Cadena();
    Cadena anio2Cadena();
};

// --- Constructores ---
Fecha::Fecha(): dia_(Fecha::Utilidades::diaActual()), mes_(Fecha::Utilidades::mesActual()), anio_(Fecha::Utilidades::anioActual()) {}

Fecha::Fecha(int d): mes_(Fecha::Utilidades::mesActual()), anio_(Fecha::Utilidades::anioActual()){

    // Comprobamos que el día sea válido
    if (d == 0) dia_ = Fecha::Utilidades::diaActual();
    else if (diaValido(d, mes_)) dia_ = d;
    else throw Invalida{"Día no válido"};
}

Fecha::Fecha(int d, int m): anio_(Fecha::Utilidades::anioActual()) {

    // Comprobamos que el mes_ sea válido
    if (m == 0) mes_ = Fecha::Utilidades::mesActual();
    else if (mesValido(m)) mes_ = m;
    else throw Invalida{"Mes no válido"};

    // Comprobamos que el día sea válido
    if (d == 0) dia_ = Fecha::Utilidades::diaActual();
    else if (diaValido(d, m)) dia_ = d;
    else throw Invalida{"Día no válido"};
}

Fecha::Fecha(int d, int m, int a) {

    // Comprobamos que el mes_ sea válido
    if (m == 0) mes_ = Fecha::Utilidades::mesActual();
    else if (mesValido(m)) mes_ = m;
    else throw Invalida{"Mes no válido"};

    // Comprobamos que el día sea válido
    if (d == 0) dia_ = Fecha::Utilidades::diaActual();
    else if (diaValido(d,m)) dia_ = d;
    else throw Invalida{"Día no válido"};

    // Comprobamos que el año sea válido
    if (a == 0) anio_ = Fecha::Utilidades::anioActual();
    else if (anioValido(a)) anio_ = a;
    else throw Invalida{"Año no válido"};
}

Fecha::Fecha(const char* f) {
    vector<vector<char>> fechaPorTrozos = transformarFechaCadena(f);

    vector<char>& vecDia = fechaPorTrozos.at(0);
    vector<char>& vecMes = fechaPorTrozos.at(1);
    vector<char>& vecAnio = fechaPorTrozos.at(2);

    int d = stoi(string{vecDia.begin(), vecDia.end()});
    int m = stoi(string{vecMes.begin(), vecMes.end()});
    int a = stoi(string{vecAnio.begin(), vecAnio.end()});

    // Comprobamos que el mes_ sea válido
    if (m == 0) mes_ = Fecha::Utilidades::mesActual();
    else if (mesValido(m)) mes_ = m;
    else throw Invalida{"Mes no válido"};;

    // Comprobamos que el día sea válido
    if (d == 0) dia_ = Fecha::Utilidades::diaActual();
    else if (diaValido(d,m)) dia_ = d;
    else throw Invalida{"Día no válido"};;

    // Comprobamos que el año sea válido
    if (a == 0) anio_ = Fecha::Utilidades::anioActual();
    else if (anioValido(a)) anio_ = a;
    else throw Invalida{"Año no válido"};;
}
// ---------------------


// --- Observadores ---
int Fecha::dia() const {
    return dia_;
}
int Fecha::mes() const {
    return mes_;
}
int Fecha::anno() const {
    return anio_;
}
// --------------------


// --- Auxiliar ---
void Fecha::imprimir() {

    Cadena d{2}, m{2}, a{};

    if (dia_ < 10){
        d[0] = '0';
        d[1] = (char) dia_;
    }
    else d[1] = (char) dia_;

    if (mes_ < 10){
        m[0] = '0';
        m[1] = (char) mes_;
    }
    else m[1] = (char) mes_;

    a = to_string(anio_).c_str();

    cout << d << "/" << m << "/" << a << endl;
}

bool Fecha::diaValido(int d, int m){
    // Día >= 1 && <= 28|29|30|31
    return d > 0 && d <= Fecha::Utilidades::maxDiaDelMes(m);
}

bool Fecha::mesValido(int m) {
    // Mes >= 1 && <= 12;
    return m > 0 && m < 13;
}

bool Fecha::anioValido(int a) {
    return a >= Fecha::AnnoMinimo && a <= Fecha::AnnoMaximo;
}

vector<vector<char>> Fecha::transformarFechaCadena(const char *f) {

    size_t longFecha = strlen(f);

    // La cadena mas corta posible solo puede ser x/x/xxxx
    if (longFecha < 8) throw Invalida{"Fecha demasiado corta"};

    // Creamos un array que contenga tres vectores
    vector<char> datos[3] = {vector<char>{}, vector<char>{}, vector<char>{}};
    vector<vector<char>> final{};
    int arrIndx = 0;
    vector<char>* vectorActual = &datos[arrIndx];

    int charIndx = 0;
    while (charIndx < longFecha){

        // Cogemos el carácter
        char actual = f[charIndx];

        // Estamos cogiendo día o mes_
        if (arrIndx < 2){

            // No es un número ni '/'
            if (!isdigit(actual) && actual != '/') throw Invalida{"Caracteres no válidos"};


            // Es un dígito, hay que añadirlo
            if (isdigit(actual)) vectorActual->push_back(actual);
                // Es '/', pasamos a buscar los datos del mes_|anio_
            else {
                arrIndx++;
                vectorActual = &datos[arrIndx];
            }
        }

            // Estamos cogiendo el año
        else {

            // Solo añadiremos números
            if (isdigit(actual)){
                vectorActual->push_back(actual);
            }
        }

        charIndx++;
    }

    for(vector<char>& v : datos){
        final.push_back(v);
    }

    return final;
}

Cadena Fecha::dia2Cadena(){
    if (dia_ < 10){
        Cadena temp{1};
        temp[0] = '0' + dia_;
        return temp;
    }
    else {
        char* numberstring = (char *) malloc((sizeof (int )) * INT16_MAX);
        sprintf(numberstring, "%d", dia_);
        return Cadena{numberstring};
    }
}
Cadena Fecha::anio2Cadena(){
    return Cadena{to_string(anio_).c_str()};
}
// -----------------


// --- Operadores ---
Fecha Fecha::operator+(int d) {
    return Fecha(*this) += d;
}
Fecha Fecha::operator-(int d) {
    return Fecha(*this) -= d;
}
Fecha& Fecha::operator+=(int d) {

    struct tm expire_time = {};
    expire_time.tm_year = anio_ - 1900;
    expire_time.tm_mon = mes_ - 1;
    expire_time.tm_mday = dia_ + d;
    //expire_time.tm_mday += d;

    // No se puede representar la fecha
    if (-1 == mktime(&expire_time)){
        throw Invalida{"Número de días incorrecto"};
    }

    // Año no válido
    int tempAnio = expire_time.tm_year + 1900;
    if (tempAnio > Fecha::AnnoMaximo || tempAnio < Fecha::AnnoMinimo){
        throw Invalida{"El año resultante no es válido"};
    }

    dia_ = expire_time.tm_mday;
    mes_ = expire_time.tm_mon + 1;
    anio_ = expire_time.tm_year + 1900;

    return *this;
}
Fecha& Fecha::operator-=(int d) {
    *this += -d;
    return *this;
}
Fecha Fecha::operator++(int d) {
    Fecha temp{*this};
    *this += 1;
    return temp;
}
Fecha Fecha::operator--(int d) {
    Fecha& f{*this};
    *this -= 1;
    return f;
}
Fecha Fecha::operator++() {
    *this += 1;
    return *this;
}
Fecha Fecha::operator--() {
    *this -= 1;
    return *this;
}
bool Fecha::operator==(const Fecha& f2) const {
    return dia_ == f2.dia_ && mes_ == f2.mes_ && anio_ == f2.anio_;
}
bool Fecha::operator<(const Fecha& f2) const{

    // Comparamos los años
    if (anio_ > f2.anio_) return false;       // Nuestro año es mayor que el otro
    else if (anio_ < f2.anio_) return true;   // Su año es mayor que el nuestro
    else {                                  // Tenemos el mismo año

        // Comparamos los años
        if (mes_ > f2.mes_) return false;     // Nuestro mes_ es mayor que el otro
        else if (mes_ < f2.mes_) return true; // Su mes_ es mayor que el nuestro
        else {                              // Tenemos el mismo mes_

            // Comparamos los días
            return dia_ < f2.dia_;
        }
    }
}
bool Fecha::operator>(const Fecha& f2) const {
    return f2 < *this;
}
bool Fecha::operator<=(const Fecha &f2) const {
    return !(f2 < *this);
}
bool Fecha::operator>=(const Fecha &f2) const {
    return !(*this < f2);
}
bool Fecha::operator!=(const Fecha &f2) const {
    return !(*this == f2);
}
// ------------------


// --- Conversores ---
Fecha::operator const char * () {

    Cadena espacio{" "};
    Cadena de{" de "};

    enTexto = Cadena{Fecha::Utilidades::diaSemana2Texto(*this)};
    enTexto += espacio;
    enTexto += dia2Cadena();
    enTexto += de;
    enTexto += Cadena{Fecha::Utilidades::mes2Texto(mes_)};
    enTexto += de;
    enTexto += anio2Cadena();

    return enTexto;
}
// ------------------

#endif //FECHA_FECHA_HPP
