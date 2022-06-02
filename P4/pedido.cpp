//
// Created by poo on 13/5/22.
//

#include "pedido.hpp"
#include "iomanip"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "articulo.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido &usuarioPedido, Pedido_Articulo &pedidoArticulo, Usuario& cliente,
               const Tarjeta& tarjeta, const Fecha &fecha): num_(N_pedidos + 1), tarjeta_(&tarjeta), fecha_(fecha), total_(0.0){

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

    // Comprobamos que haya stock (en caso de ser almacenable) o que la fecha de expiración sea posterior a la del pedido (en caso de libro digital)
    // *Nota: Si este bloque lo ponemos encima de "caducidad tarjeta", fallará un caso de prueba.
    auto compra = cliente.compra();
    for (auto it: compra) {

        // Si es un almacenable, comprobamos su stock
        if (ArticuloAlmacenable* articuloAlmacenable = dynamic_cast<ArticuloAlmacenable*>(it.first)){

            // Comprobamos el stock
            if (articuloAlmacenable->stock() < it.second){
                const_cast<Usuario::Articulos&>(cliente.compra()).clear();      // Vacimos el carrito del cliente
                throw Pedido::SinStock(it.first);                      // Lanzamos la excepcion
            }
        }

        // Es un libro digital, hay que comprobar que la fecha de expiración sea posterior a la fecha del pedido
        else if (LibroDigital* libroDigital = dynamic_cast<LibroDigital*>(it.first)){

            // Comprobamos la fecha de expiración del libro digital
            if (libroDigital->f_expir() < fecha){

                cliente.compra(*it.first, 0); // Eliminamos el LibroDigital del carrito
            }
        }
    }

    // El carrito está vacío
    if (cliente.n_articulos() == 0) throw Pedido::Vacio(cliente);

    // Actualizamos el total del pedido y el stock de cada articulo
    compra = cliente.compra();
    for (auto it: compra){

        Articulo* articulo = it.first;
        unsigned int cantidad = it.second;

        // Actualizamos el stock del artículo (si es almacenable)
        if (ArticuloAlmacenable* articuloAlmacenable = dynamic_cast<ArticuloAlmacenable*>(articulo)){
            articuloAlmacenable->stock() -= cantidad;
        }

        pedidoArticulo.pedir(*this, *articulo, articulo->precio(), cantidad);
        cliente.compra(*articulo, 0);
        total_ += articulo->precio() * cantidad;
    }



    // Asociamos al usuario con el pedido
    N_pedidos++;
    usuarioPedido.asocia(cliente, *this);
};

// TODO Comprobar como funciona el print()
std::ostream& operator << (std::ostream& os, const Pedido& pedido){
    os << "Núm. pedido: " << pedido.numero() << std::endl
    << "Fecha: " << pedido.fecha() << std::endl
    << "Pagado con: " << pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero() << std::endl
    << "Importe: " << std::fixed << std::setprecision(2) << pedido.total() << " €";
    return os;
};