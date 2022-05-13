//
// Created by poo on 13/5/22.
//

#include "pedido_articulo.hpp"
#include "iomanip"

// ----- LineaPedido -----
LineaPedido::LineaPedido(double precio_venta, unsigned int cantidad): precio_venta_(precio_venta), cantidad_(cantidad){}
std::ostream& operator << (std::ostream& os, const LineaPedido& lineaPedido){
    return os << std::fixed << std::setprecision(2) << lineaPedido.precio_venta() << " €\t" << lineaPedido.cantidad();
}
// -----------------------




// ----- Pedido_Articulo -----
void pedido_articulo::pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned int cantidad){

    LineaPedido lineaPedido(precio, cantidad);

    pedido_articulo[&pedido].insert(std::make_pair(&articulo, lineaPedido));
    articulo_pedido[&articulo].insert(std::make_pair(&pedido, lineaPedido));
}

void pedido_articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned int cantidad){
    pedir(pedido, articulo, precio, cantidad);
}

std::ostream &pedido_articulo::mostrarDetallePedidos(std::ostream &os) {

    double total = 0.0;

    for (auto i=pedido_articulo.begin(); i != pedido_articulo.end(); i++) {

        os << "Pedido núm. " << i->first->numero() << std::endl;
        os << "Cliente: " << i->first->tarjeta()->titular()->nombre();
        os << "\t\t\t Fecha: " << i->first->fecha() << std::endl;
        os << i->second;

        total += i->first->total();
    }

    os << "TOTAL VENTAS \t\t\t " << std::fixed << std::setprecision(2) << total << " €" << std::endl;

    return os;
}

std::ostream &pedido_articulo::mostrarVentasArticulos(std::ostream &os) {

    for (auto i=articulo_pedido.begin(); i != articulo_pedido.end(); i++) {

        os << "Ventas de" << (i->first)->referencia() << "] \"" << i->first->titulo() << "\"";
        os << i->second << std::endl;
    }

    return os;
}
// ---------------------------


std::ostream& operator << (std::ostream& os, const pedido_articulo::ItemsPedido& itemsPedido){

    double total = 0.0;

    os << std::endl;
    os << std::setfill(' ') << std::setw(50) << " PVP\tCantidad\t\tArtículo" << std::endl;
    os << std::setfill('=') << std::setw(50) << std::endl;

    for(auto i=itemsPedido.begin(); i != itemsPedido.end(); i++){
        os << std::fixed << std::setprecision(2) << i->second.precio_venta() << " € ";
        os << i->second.cantidad() << "\t\t";
        os << "[" << i->first->referencia() << "] \"" << i->first->titulo() << "\"" << std::endl;

        total += i->second.precio_venta() * i->second.cantidad();
    }

    os << std::setfill('=') << std::setw(50) << std::endl;
    return os << "Total\t\t" << std::fixed << std::setprecision(2) << total << " €";
}

std::ostream& operator << (std::ostream& os, const pedido_articulo::Pedidos& pedidos){

    double total = 0.0;
    unsigned int cantidad = 0;

    os << std::endl;
    os << std::setfill(' ') << std::setw(50) << " PVP \t Cant. \t Fecha venta" << std::endl;
    os << std::setfill('=') << std::setw(50) << std::endl;

    for(auto i=pedidos.begin(); i != pedidos.end(); i++){
        os << std::fixed << std::setprecision(2) << i->second.precio_venta() << " € \t ";
        os << i->second.cantidad() << " \t ";
        os << i->first->fecha() << std::endl;

        total += i->second.precio_venta() * i->second.cantidad();
        cantidad += i->second.cantidad();
    }

    os << std::setfill('=') << std::setw(50) << std::endl;
    return os << std::fixed << std::setprecision(2) << total << " €" << "\t\t\t" << cantidad;
}