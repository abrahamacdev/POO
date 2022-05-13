//
// Created by poo on 13/5/22.
//

#include "usuario_pedido.h"

void Usuario_Pedido::asocia(Usuario &usuario, Pedido &pedido) {
    usuario_pedidos[&usuario].insert(&pedido);
    pedido_usuario[&pedido] = &usuario;
}

void Usuario_Pedido::asocia(Pedido &pedido, Usuario &usuario) {
    asocia(usuario, pedido);
}
