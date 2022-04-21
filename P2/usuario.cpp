//
// Created by poo on 21/4/22.
//

#include "usuario.h"


// Constructores
Usuario::Usuario(const Cadena &identificador, const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion):
    identificador_(identificador), nombre_(nombre), apellidos_(apellidos), direccion_(direccion){

    // Comprobamos que no halla un usuario con el mismo identificador
    if(!listadoUsuarios.insert(identificador).second) throw Id_duplicado(identificador);
}

// Asociación con la clase Tarjeta

// Asociacion con la clase artículo
void Usuario::compra(Articulo &articulo, unsigned int cantidad) {

    // ELiminamos el articulo del carrito
    if (cantidad == 0){
        carrito.erase(&articulo);
    }
    else {
       carrito.insert(std::make_pair(&articulo, cantidad));
    }
}

// Operadores
// TODO Faltan

Usuario::~Usuario() {
    auto iterador = carrito.begin();

    while (iterador != carrito.end()){
        // Eliminamos el artículo de la cesta
        carrito.erase(iterador);

        iterador++;
    }
}
