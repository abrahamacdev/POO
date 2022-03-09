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

    // Conversores
    operator const char * ();

    // Operadores
    Cadena& operator =(const Cadena& c2);
    Cadena& operator =(const char* c2);
    Cadena& operator +=(const Cadena& c2);
    Cadena operator +(const Cadena& c2);
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

        static Cadena vector2Cadena(std::vector<char>& v){
            unsigned int tam = v.size();
            Cadena temp(tam);

            for (int i = 0; i < tam; ++i) {
                temp[i] = v[i];
            }

            return temp;
        }
        static Cadena numero2Cadena(int n){

            if (n < 0) throw std::runtime_error("No se puede transformar actualmente");

            std::vector<char> vector{};

            Cadena final{};
            int entera = n;

            while (entera > 0){

                int temp = entera / 10;
                int decimal = entera % 10;
                entera = temp;

                vector.push_back((char) ('0' + decimal));
            }
            std::reverse(vector.begin(), vector.end());
            return vector2Cadena(vector);
        }
    };

private:
    void eliminar();
};


// --- Constructores ---
Cadena::Cadena(): s_(new char[1]()), tam_(0) {
    s_[0] = '\0';    // Caracter final
}
Cadena::Cadena(unsigned int tamanio, const char  relleno): s_(new char[tamanio+1]()), tam_(tamanio) {
    for (unsigned int i=0; i < tamanio; i++){
        s_[i] = relleno;
    }
    s_[tamanio] = '\0';     // Caracter final
}
Cadena::Cadena(unsigned int tamanio): s_(new char[tamanio+1]()), tam_(tamanio) {
    for (unsigned int i=0; i < tamanio; i++){
        s_[i] = ' ';
    }
    s_[tamanio] = '\0';     // Caracter final
}
inline Cadena::Cadena(const Cadena &c) {
    s_ = new char[c.tam_ + 1]();
    strcpy(s_, c.s_);
    tam_ = c.tam_;
}
Cadena::Cadena(const char* a) {
    tam_ = strlen(a);
    s_ = new char[tam_ + 1]();
    strcpy(s_, a);
}
// ---------------------


//  --- Observadores ---
const char& Cadena::at(size_t i) const {
    if (i < 0 || i > tam_ - 1) throw std::out_of_range("Índice no válido");
    return s_[i];
}
char& Cadena::at(size_t i) {
    if (i < 0 || i > tam_ - 1) throw std::out_of_range("Índice no válido");
    return s_[i];
}
Cadena Cadena::substr(unsigned int indx, unsigned int tam) {

    // Comprobamos que esté en un rango válido
    if (indx < 0 || indx > tam_ - 1) throw std::out_of_range("Índice no válido");

    // Calculamos si hay suficientes caracteres
    unsigned int diff = tam_ - indx;
    if (diff < tam) throw std::out_of_range("No hay tanto caracteres");

    Cadena nueva{tam};
    for (unsigned int i = indx; i < indx + tam; ++i) {
        char c = s_[i + indx];
        nueva[i - indx] = s_[i];
    }

    return nueva;
}
// ---------------------


// --- Operadores --
Cadena& Cadena::operator=(const Cadena &c2) {

    // Comprobamos que nos sea la misma instancia
    if (this != &c2){

        // Eliminamos los datos de la cadena actual
        eliminar();

        // Copiamos el tamaño y el contenido
        tam_ = c2.tam_;
        s_ = new char[c2.tam_ + 1]();
        strcpy(s_, c2.s_);
    }

    return *this;
}
Cadena& Cadena::operator=(const char* c2){
    eliminar();

    tam_ = strlen(c2);
    s_ = new char[tam_ + 1];
    strcpy(s_, c2);
}
Cadena& Cadena::operator +=(const Cadena& c2){

    char* temp = new char[tam_ + c2.tam_ + 1]();
    strcpy(temp, s_);
    strcat(temp, c2.s_);
    tam_ += c2.tam_;

    delete[] s_;
    s_ = temp;

    return *this;
}
Cadena Cadena::operator+(const Cadena &c2) {

    char* temp = new char[tam_ + c2.tam_ + 1];
    strcpy(temp, s_);
    strcat(temp, c2.s_);

    return Cadena{temp};
}
bool Cadena::operator==(const Cadena &c2) {
    return strcmp(s_, c2.s_) == 0;
}
bool Cadena::operator<(const Cadena &c2) {
    return strcmp(s_, c2.s_) == -1;
}
bool Cadena::operator<=(const Cadena &c2) {
    return !(*this > c2);
}
bool Cadena::operator>(const Cadena &c2) {
    return strcmp(s_, c2.s_) == 1;
}
bool Cadena::operator>=(const Cadena &c2) {
    return !(*this < c2);
}
bool Cadena::operator!=(const Cadena &c2) {
    return !(*this == c2);
}
char& Cadena::operator[](unsigned int i) {
    return s_[i];
}
const char& Cadena::operator[](unsigned int i) const {
    return s_[i];
}
// -----------------


// --- Conversor ---
Cadena::operator const char *() {
    return s_;
}
// -----------------


void Cadena::eliminar() {
    delete[] s_;
}

Cadena::~Cadena() {
    eliminar();
}

#endif //FECHA_CADENA_HPP