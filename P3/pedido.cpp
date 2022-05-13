//
// Created by poo on 13/5/22.
//

#include "pedido.hpp"
#include "iomanip"

Pedido::Pedido(const Usuario_Pedido &usuarioPedido, const pedido_articulo &pedidoArticulo, const Usuario *cliente,
               const Tarjeta *tarjeta, const Fecha &fecha): num_(++N_pedidos), tarjeta_(tarjeta), fecha_(fecha), total_(0.0){

    // TODO Llamar a la correspondiente funcioón de pedidoArticulo (pág 4)
    // El carrito está vacío
    //if (pedidoArticulo.vacio()) throw Pedido::Vacio(cliente);

    // El titular de la tarjeta no coincide con el cliente que hace el pedido
    if (tarjeta->titular() != cliente) throw Pedido::Impostor(cliente);

    // TODO Llamar a las correspondientes funciones de pedidoArticulo y usuarioPedido (pág 5)
    // Algún artículo del carrito supera las existencias en almacén

    // Comprobamos si la tarjeta está caducada
    if (tarjeta->caducidad() < fecha){

    }

    // Comprobamos que la tarjeta esté activa
    if (!tarjeta->activa()) throw Tarjeta::Desactivada{};


};

// TODO Comprobar como funciona el print()
std::ostream& operator << (std::ostream& os, const Pedido& pedido){
    return os << "Núm. pedido: " << pedido.numero() << std::endl
    << "Fecha:" << std::setfill(' ') <<  std::setw(50) << pedido.fecha() << std::endl
    << "Pagado con: " << std::setfill(' ') <<  std::setw(50) << pedido.tarjeta()->tipo() << " nº: " << pedido.tarjeta()->numero() << std::endl
    << "Importe: " << std::setfill(' ') <<  std::setw(50) << std::fixed << std::setprecision(2) << pedido.total() << "€";
};