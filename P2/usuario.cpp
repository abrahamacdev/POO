//
// Created by poo on 21/4/22.
//

#include "iomanip"
#include "unistd.h"
#include "random"

#include "usuario.hpp"

// ********** Clase "Clave" **********
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
// ************************************





// ********** Clase "Usuario" **********
// Inicializamos la variable estática
Usuario::Usuarios Usuario::listadoUsuarios;

// Constructores
Usuario::Usuario(const Cadena &identificador, const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion, const Clave& clave):
    identificador_(identificador), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), clave_(clave){

    // Comprobamos que no halla un usuario con el mismo identificador
    if(!listadoUsuarios.insert(identificador).second) throw Id_duplicado(identificador);
}

// Asociación con la clase Tarjeta
void Usuario::es_titular_de(Tarjeta& tarjeta) {

    // Comprobamos que ya seamos titulares de la tarjeta en el objeto tarjeta
    if (this == tarjeta.titular()){

        // Comprobamos si ya estaba en el map
        if (!tarjetas_.insert(std::make_pair(tarjeta.numero(), &tarjeta)).second){
            throw Tarjeta::Num_duplicado(tarjeta.numero());
        }
    }
}
void Usuario::no_es_titular_de(Tarjeta &tarjeta) {
    tarjeta.anula_titular();
    tarjetas_.erase(tarjeta.numero());
}

// Asociacion con la clase artículo
void Usuario::compra(Articulo &articulo, unsigned int cantidad) {

    // ELiminamos el articulo del carrito
    if (cantidad == 0){
        carrito.erase(&articulo);
    }
    else {
        carrito[&articulo] = cantidad;
    }
}

// Operadores
std::ostream &operator<<(std::ostream &os, const Usuario &usuario) {

    os << usuario.identificador_ << "[" << usuario.clave_.clave().c_str() << "]" << usuario.nombre_ << usuario.apellidos_ << std::endl
       << usuario.direccion_ << std::endl
       << "Tarjetas: " ;
    for(const auto &tarjeta : usuario.tarjetas_){
        os << *tarjeta.second << std::endl;
    }

    return os ;
}

void mostrar_carro(std::ostream& os, const Usuario& usuario){

    os << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << std::endl
       << "Cant. Artículo" << std::endl
       << std::setw(50) << std::setfill('=') << "" << std::endl;

    auto i = usuario.compra().begin();
    while (i != usuario.compra().end()){

        os << std::setw(3) << std::setfill(' ') << i->second << std::setw(4) << std::setfill(' ') <<  *i->first << std::endl;
        i++;
    }
}

Usuario::~Usuario() {
    auto iterador = tarjetas_.begin();

    // Anulamos la tarjeta
    while (iterador != tarjetas_.end()){
        iterador->second->anula_titular();

        iterador++;
    }

    // Nos eliminamos del listado de usuarios
    listadoUsuarios.erase(identificador_);
}
// ************************************