//
// Created by poo on 13/5/22.
//

#include "Pedido_Articulo.hpp"
#include "iomanip"

LineaPedido::LineaPedido(double precio_venta, unsigned int cantidad): precio_venta_(precio_venta), cantidad_(cantidad){}

std::ostream& operator << (std::ostream& os, const LineaPedido& lineaPedido){
    return os << std::fixed << std::setprecision(2) << lineaPedido.precio_venta() << " €\t" << lineaPedido.cantidad();
}