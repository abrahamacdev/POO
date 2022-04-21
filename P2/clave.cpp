//
// Created by poo on 21/4/22.
//

#include "clave.h"

Clave::Clave(const char *contrasenia) {

    // Comprobamos que la contraseña tenga al menos 5 caracteres
    if (strlen(contrasenia) < 5) throw Incorrecta(Razon::CORTA);
}
