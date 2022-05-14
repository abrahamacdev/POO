//
// Created by poo on 13/5/22.
//

#include "pedido.hpp"
#include "iomanip"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido &usuarioPedido, Pedido_Articulo &pedidoArticulo, Usuario& cliente,
               const Tarjeta& tarjeta, const Fecha &fecha): num_(++N_pedidos), tarjeta_(&tarjeta), fecha_(fecha), total_(0.0){

    // El carrito está vacío
    if (cliente.n_articulos() == 0) throw Pedido::Vacio(cliente);

    // El titular de la tarjeta no coincide con el cliente que hace el pedido
    if (tarjeta.titular() != &cliente) throw Pedido::Impostor(cliente);

    // Comprobamos si la tarjeta está caducada
    if (tarjeta.caducidad() < fecha){
        throw Tarjeta::Caducada{tarjeta.caducidad()};
    }

    // Comprobamos que la tarjeta esté activa
    if (!tarjeta.activa()) throw Tarjeta::Desactivada{};

    // Algún artículo del carrito supera las existencias en almacén
    // *Nota: Si este bloque lo ponemos encima de "caducidad tarjeta", fallará un caso de prueba.
    for (auto it: cliente.compra()) {
        if (it.first->stock() < it.second){
            const_cast<Usuario::Articulos&>(cliente.compra()).clear();      // Vacimos el carrito del cliente
            throw Pedido::SinStock(it.first);                      // Lanzamos la excepcion
        }
    }


    // Actualizamos el total del pedido y el stock de cada articulo
    auto compra = cliente.compra();
    for (auto it: compra){

        Articulo* articulo = it.first;
        unsigned int cantidad = it.second;

        // Actualizamos el stock del artículo
        articulo->stock() -= cantidad;

        pedidoArticulo.pedir(*this, *articulo, articulo->precio(), cantidad);
        cliente.compra(*articulo, 0);
        total_ += articulo->precio() * cantidad;
    }



    // Asociamos al usuario con el pedido
    usuarioPedido.asocia(cliente, *this);
};

// TODO Comprobar como funciona el print()
std::ostream& operator << (std::ostream& os, const Pedido& pedido){
    os << "Núm. pedido: " << pedido.numero() << std::endl
    << "Fecha:" << std::setfill(' ') <<  std::setw(50) << pedido.fecha() << std::endl
    << "Pagado con: " << std::setfill(' ') <<  std::setw(50) << pedido.tarjeta()->tipo() << " nº: " << pedido.tarjeta()->numero() << std::endl
    << "Importe: " << std::setfill(' ') <<  std::setw(50) << std::fixed << std::setprecision(2) << pedido.total() << "€";
    return os;
};