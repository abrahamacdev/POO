#include "numero.hpp"
#include "../luhn.cpp"

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
