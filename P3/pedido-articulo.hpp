//
// Created by poo on 13/5/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_PEDIDO_ARTICULO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_PEDIDO_ARTICULO_HPP

#include "map"
#include "pedido.hpp"
#include "articulo.hpp"

struct OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool> {
    bool operator()(const Pedido* pedido1, const Pedido* pedido2) const {
        return pedido1->numero() < pedido2->numero();
    }
};

struct OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool> {
    bool operator()(const Articulo* articulo1, const Articulo* articulo2) const {
        return articulo1->referencia() < articulo2->referencia();
    }
};

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


class Pedido_Articulo {

    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        void pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned int cantidad = 1);
        void pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned int cantidad = 1);

        inline ItemsPedido detalle(Pedido& pedido) const {
            auto it = pedido_articulo.find(&pedido);
            if (it != pedido_articulo.end()) return it->second;
            return ItemsPedido();
        };
        inline Pedidos ventas(Articulo& articulo) const {
            auto it = articulo_pedido.find(&articulo);
            if (it != articulo_pedido.end()) return it->second;
            return Pedidos();
        };

        void mostrarDetallePedidos(std::ostream& os);
        void mostrarVentasArticulos(std::ostream& os);

    private:
        std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedido_articulo;
        std::map<Articulo*, Pedidos, OrdenaArticulos> articulo_pedido;
};

std::ostream& operator << (std::ostream& os, const Pedido_Articulo::ItemsPedido& itemsPedido);
std::ostream& operator << (std::ostream& os, const Pedido_Articulo::Pedidos& pedidos);


#endif //ALVAREZ_CRUZ_ABRAHAM_PEDIDO_ARTICULO_HPP
