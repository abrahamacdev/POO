//
// Created by poo on 13/5/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_PEDIDO_ARTICULO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_PEDIDO_ARTICULO_HPP

#include "iostream"
#include "map"
#include "pedido.hpp"
#include "articulo.hpp"

class LineaPedido {

public:
    explicit LineaPedido(double precio_venta, unsigned int cantidad = 1);

    inline double precio_venta() const { return precio_venta_; };
    inline unsigned int cantidad() const { return cantidad_; };

private:
    double precio_venta_;
    unsigned int cantidad_;
};
std::ostream& operator << (std::ostream& os, const LineaPedido& lineaPedido);


class OrdenaPedidos: std::binary_function<Pedido*, Pedido*, bool> {

    bool operator()(const Pedido* pedido1, const Pedido* pedido2) const {
        return pedido1->numero() < pedido2->numero();
    }
};

class OrdenaArticulos: std::binary_function<Articulo*, Articulo*, bool> {

    bool operator()(const Articulo* articulo1, const Articulo* articulo2) const {
        return articulo1->referencia() < articulo2->referencia();
    }
};


class Pedido_Articulo {

    public:
        typedef std::map<Pedido*, LineaPedido*, OrdenaPedidos> Pedidos;
        typedef std::map<Articulo*, LineaPedido*, OrdenaArticulos> Articulos;

    private:

        std::map<Pedido*, Articulos, OrdenaPedidos> pedidos_;
        std::map<Articulo*, Pedidos, OrdenaArticulos> articulos_;

};


#endif //ALVAREZ_CRUZ_ABRAHAM_PEDIDO_ARTICULO_HPP
