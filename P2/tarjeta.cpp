//
// Created by poo on 21/4/22.
//

#include <iomanip>

#include "tarjeta.hpp"

bool luhn(const Cadena& num);

// ********** Clase "Numero" **********
Numero::Numero(const Cadena &numero){

    Cadena copia = Cadena(numero.length());

    // Vamos copiando a la cadena "copia" toddo aquello que no sea un espacio
    int j=0;
    for (int i = 0; i < numero.length(); ++i) {

        // Comprobamos que el caracter no sea un espacio
        if (!isspace(numero[i])){

            // Comprobamos que si no es un dígito para lanzar el error
            if (!isdigit(numero[i])) throw Numero::Incorrecto(Razon::DIGITOS);

            copia[j] = numero[i];
            j++;
        }
    }

    // Ajustamos la cadena al tamaño que debe tener
    if (j != numero.length() - 1){
        copia = Cadena(copia.substr(0, j));
    }

    // Comprobamos que la longitud de la cadena ("copia") sea válida
    if (copia.length() < 13 || copia.length() > 19) throw Numero::Incorrecto(Razon::LONGITUD);

    // No pasa el algoritmo de Luhn
    if (!luhn(copia)) throw Numero::Incorrecto(Razon::NO_VALIDO);

    // Una vez pasado toddo, guardamos el número
    numero_ = copia;
}

// Operadores
Numero::operator const char*() const{ return numero_.c_str(); }

bool operator<(const Numero &numero1, const Numero &numero2) { return strcmp(numero1, numero2) < 0; }
// ************************************





// ********** Clase "Tarjeta" **********
Tarjeta::Tarjeta(const Numero &numeroTarjeta, const Usuario &titular, const Fecha &caducidad): numeroTarjeta_(numeroTarjeta), titular_(&titular),
                                                                                               caducidad_(caducidad), activa_(true) {
    // Comprobamos que la fecha sea >= que hoy
    if (caducidad < Fecha()) throw Caducada(caducidad);

    // EL usuario nos guardara en su listado de tarjetas_
    (const_cast<Usuario&>(titular)).es_titular_de(*this);

}
bool Tarjeta::activa(bool activar) {
    activa_ = activar;
    return activa_;
}

void Tarjeta::anular_tarjeta() {
    titular_ = nullptr;
    activa_ = false;
}

Tarjeta::Tipo Tarjeta::tipo() const {

    const char* numero = numeroTarjeta_;

    switch (numero[0]) {

        case '3':

            // 34 ó 37
            if (numero[1] == '4' || numero[1] == '7'){
                return Tipo::AmericanExpress;
            }

            // 3x (salvo 34 y 37)
            else {
                return Tipo::JCB;
            }
            break;

        case '4':
            return Tipo::VISA;
            break;

        case '5':
            return Tipo::Mastercard;
            break;

        case '6':
            return Tipo::Maestro;
            break;

        default:
            return Tipo::Otro;
            break;
    }
}

Tarjeta::~Tarjeta() {

    // Comprobamos que el Usuario no halla sido eliminado
    if (titular_){
        const_cast<Usuario&>(*titular_).no_es_titular_de(*this);
    }

}

std::ostream& operator<<(std::ostream &os, const Tarjeta& tarjeta) {

    Cadena nombre = Cadena(tarjeta.titular_->nombre());          // Creamos una copia para no modificar la cadena original
    Cadena apellidos = Cadena(tarjeta.titular_->apellidos());

    for (char& n : nombre) {
        n = toupper(n);
    }

    for (char& a : apellidos) {
        a = toupper(a);
    }

    return os << tarjeta.tipo() << std::endl
        << tarjeta.numeroTarjeta_ << std::endl
        << nombre << " " << apellidos << std::endl
        << "Caduca: " << std::setfill('0') << std::setw(2) << tarjeta.caducidad_.mes() << "/" << std::setw(2) << (tarjeta.caducidad_.anno() % 100 );
}

std::ostream& operator << (std::ostream& os, const Tarjeta::Tipo& tipo){
    switch(tipo){
        case 0: os << "Otro" ; break;
        case 1: os << "VISA" ; break ;
        case 2: os << "Mastercard"; break ;
        case 3: os << "Maestro"; break ;
        case 4: os << "JCB" ; break ;
        case 5: os << "AmericanExpress" ; break ;
        default: os << "Otra"; break ;
    }

    return os ;
}

bool operator<(const Tarjeta& t1, const Tarjeta& t2){
    return t1.numeroTarjeta_ < t2.numeroTarjeta_;
}
// ************************************