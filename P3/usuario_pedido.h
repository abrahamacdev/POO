//
// Created by poo on 13/5/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_USUARIO_PEDIDO_H
#define ALVAREZ_CRUZ_ABRAHAM_USUARIO_PEDIDO_H

#include "pedido.hpp"
#include "usuario.hpp"
#include "set"

class Usuario_Pedido {

    public:
        typedef std::set<Pedido*> Pedidos;

        void asocia(Usuario& usuario, Pedido& pedido);
        void asocia(Pedido& pedido, Usuario& usuario);

        inline Pedidos& pedidos(Usuario& usuario) { return usuario_pedidos[&usuario]; };
        inline Usuario* cliente(Pedido& pedido) { return pedido_usuario[&pedido]; };

    private:
        std::map<Usuario*, Pedidos> usuario_pedidos;
        std::map<Pedido*, Usuario*> pedido_usuario;
};


#endif //ALVAREZ_CRUZ_ABRAHAM_USUARIO_PEDIDO_H
