//
// Created by poo on 21/4/22.
//

#define _XOPEN_SOURCE
#include "unistd.h"
#include "random"
#include "clave.hpp"

Clave::Clave(const char *contrasenia) {

    // Conjunto de caracteres que se usarán para el salt
    static const char* caracteres = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};

    // Comprobamos que la contraseña tenga al menos 5 caracteres
    if (strlen(contrasenia) < 5) throw Clave::Incorrecta(Razon::CORTA);

    // Generador de números aleatorios
    std::random_device dev;
    std::mt19937 rng(dev());    // Motor usado para la generación del número aleatorio (Mersenne Twister)
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,strlen(caracteres)); // Distribución en el rango [0, #len(caracteres)]

    // Generamos el salt de manera aleatoria
    char* salt = new char[tamanioSalt_];
    for (int i = 0; i < tamanioSalt_; ++i) {
        salt[i] = caracteres[dist(rng)];
    }

    // Ciframos la contraseña con el salt recién generado
    const char* cifrada = crypt(contrasenia, salt);

    // No se ha podido cifrar la clave
    if (cifrada == nullptr) std::throw_with_nested(Clave::Incorrecta(Razon::ERROR_CRYPT));
    else {
        // Guardamos la contraseña cifrada
        contrasenia_ = Cadena(cifrada);
    }
}

bool Clave::verifica(const char *c) const {
    return strcmp(crypt(c, contrasenia_.c_str()), contrasenia_.c_str()) == 0;
}


