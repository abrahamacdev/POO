//
// Created by poo on 21/4/22.
//

#include "articulo.hpp"
#include "iomanip"

// ----- Autor -----
Autor::Autor(const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion) noexcept: nombre_(nombre), apellidos_(apellidos),
                                                                                               direccion_(direccion){}
// -----------------


// ----- Articulo -----
Articulo::Articulo(const Autores& autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion,
                   double precio): autores_(autores), referencia_(referencia), titulo_(titulo),
                   publicacion_(publicacion), precio_(precio){

    // Todo artículo tendrá, al menos, un autor
    if (autores.size() == 0) throw Articulo::Autores_vacios(autores);
}
std::ostream &operator<<(std::ostream &os, const Articulo &articulo) {

    // Impresión común a todos los artículos
    os << "[" << std::setw(3) << std::setfill('0') << articulo.referencia() << "] \"" << articulo.titulo() << "\", de ";

    for (auto i = articulo.autores().begin(); i != articulo.autores().end(); i++) {
        os << (*i)->apellidos();

        // Si no es el último elemento, pone una ","
        if (++i != articulo.autores().end()){
            os << ", ";
        }
        i--;
    }
    os << ". " << articulo.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << articulo.precio() << " €" << std::endl << "\t";

    // Impresión específica
    articulo.impresion_especifica(os);
    return os;
}
// ---------------------



// ----- ArticuloAlmacenable -----
ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion,
                                         double precio, unsigned int stock):
                                         Articulo(autores, referencia, titulo, publicacion, precio), stock_(stock) {}
// -------------------------------



// ----- Libro -----
Libro::Libro(const Autores& autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion, double precio,
             unsigned int n_pag, unsigned int stock): ArticuloAlmacenable(autores, referencia, titulo, publicacion, precio, stock), n_pag_(n_pag){};

void Libro::impresion_especifica(std::ostream &os) const {
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}
// -----------------



// ----- Cederron -----
Cederron::Cederron(const Autores& autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion, double precio,
                   unsigned int tam, unsigned int stock): ArticuloAlmacenable(autores, referencia, titulo, publicacion, precio, stock), tam_(tam) {}

void Cederron::impresion_especifica(std::ostream &os) const {
    os << tam_ << " MB, " << stock_ << " unidades.";
}
// --------------------



// ----- Libro Digital -----
LibroDigital::LibroDigital(const Autores& autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion, double precio,
                           const Fecha &expiracion): Articulo(autores, referencia, titulo, publicacion, precio), f_expir_(expiracion) {
}
void LibroDigital::impresion_especifica(std::ostream &os) const {
    os << "A la venta hasta el " << f_expir_ << ".";
}
// -------------------------