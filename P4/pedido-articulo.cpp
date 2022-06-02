//
// Created by poo on 13/5/22.
//

#include "pedido-articulo.hpp"
#include "iomanip"
#include "locale"

// ----- LineaPedido -----
LineaPedido::LineaPedido(double precio_venta, unsigned int cantidad): precio_venta_(precio_venta), cantidad_(cantidad){}
std::ostream& operator << (std::ostream& os, const LineaPedido& lineaPedido){
    return os << std::fixed << std::setprecision(2) << lineaPedido.precio_venta() << " €\t" << lineaPedido.cantidad();
}
// -----------------------




// ----- Pedido_Articulo -----
void Pedido_Articulo::pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned int cantidad){

    articulo_pedido[&articulo].insert(std::make_pair(&pedido, LineaPedido(precio, cantidad)));
    pedido_articulo[&pedido].insert(std::make_pair(&articulo, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned int cantidad){
    pedir(pedido, articulo, precio, cantidad);
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream &os) {

    double total = 0.0;

    for (auto i=pedido_articulo.begin(); i != pedido_articulo.end(); i++) {

        Pedido* pedido = i->first;

        os << "Pedido núm. " << pedido->numero() << std::endl;
        os << "Cliente: " << pedido->tarjeta()->titular()->nombre();
        os << "\t\t\t Fecha: " << pedido->fecha() << std::endl;
        os <<  detalle(*(i->first));

        total += pedido->total();
    }

    os << "TOTAL VENTAS \t\t\t " << std::fixed << std::setprecision(2) << total << " €" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &os) {

    for (auto i=articulo_pedido.begin(); i != articulo_pedido.end(); i++) {

        Articulo* articulo = i->first;

        os << "Ventas de [" << articulo->referencia() << "] \"" << articulo->titulo() << "\"";
        os << ventas(*(i->first)) << std::endl;
    }

}
// ---------------------------


std::ostream& operator << (std::ostream& os, const Pedido_Articulo::ItemsPedido& itemsPedido){

    double total = 0.0;

    os << " PVP \t Cantidad \t\t Artículo" << std::endl;
    os << std::setw(50) << std::setfill('=') << "" << std::endl;

    for(auto i=itemsPedido.begin(); i != itemsPedido.end(); i++){
        os << std::setw(5) << std::left << std::setfill(' ') << std::fixed << std::setprecision(2) << i->second.precio_venta() << " €  ";
        os << std::setw(8) << i->second.cantidad() << " \t\t ";
        os <<  "[" << i->first->referencia() << "] \"" << i->first->titulo() << "\"" << std::endl;

        total += i->second.precio_venta() * i->second.cantidad();
    }

    os << std::setw(50) << std::setfill('=') << "" << std::endl;
    return os << "Total\t" << std::fixed << std::setprecision(2) << total << " €" << std::endl << std::endl;
}

std::ostream& operator << (std::ostream& os, const Pedido_Articulo::Pedidos& pedidos){

    double total = 0.0;
    unsigned int cantidad = 0;

    os << std::endl;
    os << std::setfill(' ') << std::setw(50) << " PVP \t Cant. \t Fecha venta" << std::endl;
    os << std::setw(50) << std::setfill('=') << "" << std::endl;

    for(auto i=pedidos.begin(); i != pedidos.end(); i++){
        os << " " << i->second.precio_venta() << " € \t ";
        os << i->second.cantidad() << " \t ";
        os << i->first->fecha() << std::endl;

        total += i->second.precio_venta() * i->second.cantidad();
        cantidad += i->second.cantidad();
    }

    os << std::setw(50) << std::setfill('=') << "" << std::endl;
    return os << std::fixed << std::setprecision(2) << total << " €" << "\t\t" << cantidad;
}