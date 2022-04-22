//
// Created by poo on 21/4/22.
//

#include "usuario.hpp"
#include "iomanip"

// Constructores
Usuario::Usuario(const Cadena &identificador, const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion, const Clave& clave):
    identificador_(identificador), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), clave_(clave){

    // Comprobamos que no halla un usuario con el mismo identificador
    if(!listadoUsuarios.insert(identificador).second) throw Id_duplicado(identificador);
}

// Asociación con la clase Tarjeta
void Usuario::es_titular(Tarjeta& tarjeta) {

    // Comprobamos que ya seamos titulares de la tarjeta en el objeto tarjeta
    if (this == tarjeta.titular()){

        // Comprobamos si ya estaba en el map
        if (!tarjetas.insert(std::make_pair(tarjeta.numero(), &tarjeta)).second){
            throw Tarjeta::Num_duplicado(tarjeta.numero());
        }
    }
}
void Usuario::no_es_titular_de(Tarjeta &tarjeta) {
    tarjeta.anular_tarjeta();
    tarjetas.erase(tarjeta.numero());
}

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
std::ostream &operator<<(std::ostream &os, const Usuario &usuario) {

    os << usuario.identificador_ << "[" << usuario.clave_.clave().c_str() << "]" << usuario.nombre_ << usuario.apellidos_ << std::endl
       << usuario.direccion_ << std::endl
       << "Tarjetas: " ;
    for(const auto &tarjeta : usuario.tarjetas){
        os << *tarjeta.second << std::endl;
    }

    return os ;
}

/*void mostrar_carro(std::ostream& os, const Usuario& usuario){
    os << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << "\n"
       << "Cant.Artículo" << std::endl
       << std::setw(95) << std::setfill('=') << '\n' << std::setfill(' ');

    int nart = usuario.n_articulos() ;

    while( nart > 0 )
    {
        for(auto i = usuario.compra().begin(); i != usuario.compra().end(); i++){
            os << std::setw(4) << i->second << "    "
                   << " [" << (*i->first).referencia() << "] " << "\""
                   << (*i->first).titulo() << "\", "
                   << (*i->first).f_publi().anno()
                   << ". " << std::fixed << std::setprecision(2) << (*i->first).precio() << " €" << std::endl;

            --nart;
        }
    }

    return os;
}*/

Usuario::~Usuario() {
    auto iterador = tarjetas.begin();

    // Anulamos la tarjeta
    while (iterador != tarjetas.end()){
        iterador->second->anular_tarjeta();

        iterador++;
    }

    // Nos eliminamos del listado de usuarios
    listadoUsuarios.erase(identificador_);
}
