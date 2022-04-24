//
// Created by poo on 21/4/22.
//

#include "articulo.hpp"
#include "iomanip"

Articulo::Articulo(const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion, double precio,
                   unsigned int existencias): referencia_(referencia), titulo_(titulo), publicacion_(publicacion), precio_(precio), existencias_(existencias) {}

std::ostream &operator<<(std::ostream &os, const Articulo &articulo) {

    return os << "[" << articulo.referencia_ << "] \"" << articulo.titulo_ << "\", " << articulo.publicacion_.anno() << ". " << std::fixed << std::setprecision(2) << articulo.precio_ << " €";
}


