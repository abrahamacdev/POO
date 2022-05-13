//
// Created by poo on 13/5/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_PEDIDO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_PEDIDO_HPP

#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"

class Usuario_Pedido;
class pedido_articulo;

class Pedido {

    public:

        class Vacio {

            public:
                Vacio(const Usuario* usuario): usuario_(usuario){}

                inline const Usuario* usuario() const { return usuario_; };

            private:
                const Usuario* usuario_;
        };

        class Impostor{

            public:
                Impostor(const Usuario* usuario): usuario_(usuario){}

                inline const Usuario* usuario() const { return usuario_; };

            private:
                const Usuario* usuario_;
        };

        class SinStock{

            public:
                SinStock(const Articulo* articulo): articulo_(articulo){}

                inline const Articulo* articulo() const { return articulo_; };

            private:
                const Articulo* articulo_;
        };


        Pedido(const Usuario_Pedido& usuarioPedido, const pedido_articulo& pedidoArticulo, const Usuario* cliente,
               const Tarjeta* tarjeta, const Fecha& fecha = Fecha());


        // Observadores
        inline int numero() const { return num_; };
        inline const Tarjeta* tarjeta() const { return tarjeta_; };
        inline const Fecha& fecha() const { return fecha_; };
        inline double total() const { return total_; };
        inline static int n_total_pedidos() { return N_pedidos; };      // Del atributo estático

    private:
        int num_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;

        static int N_pedidos;
};

std::ostream& operator << (std::ostream& os, const Pedido& pedido);

#endif //ALVAREZ_CRUZ_ABRAHAM_PEDIDO_HPP
