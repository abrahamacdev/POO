//
// Created by poo on 13/5/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_PEDIDO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_PEDIDO_HPP

#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include "articulo.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido {

    public:

        class Vacio {

            public:
                Vacio(Usuario& usuario): usuario_(&usuario){}

                Usuario& usuario() const { return *usuario_; };

            private:
                Usuario* usuario_;
        };

        class Impostor{

            public:
                Impostor(Usuario& usuario): usuario_(&usuario){}

                Usuario& usuario() const { return *usuario_; };

            private:
                Usuario* usuario_;
        };

        class SinStock{

            public:
                SinStock(Articulo* articulo): articulo_(articulo){}

                Articulo& articulo() const {
                    return *articulo_;
                };

            private:
                Articulo* articulo_;
        };


        Pedido(Usuario_Pedido& usuarioPedido, Pedido_Articulo& pedidoArticulo, Usuario& cliente, const Tarjeta& tarjeta, const Fecha& fecha = Fecha());


        // Observadores
        int numero() const { return num_; };
        const Tarjeta* tarjeta() const { return tarjeta_; };
        const Fecha& fecha() const { return fecha_; };
        double total() const { return total_; };
        static int n_total_pedidos() { return N_pedidos; };      // Del atributo estático

    private:
        int num_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;

        static int N_pedidos;
};

std::ostream& operator << (std::ostream& os, const Pedido& pedido);

#endif //ALVAREZ_CRUZ_ABRAHAM_PEDIDO_HPP
