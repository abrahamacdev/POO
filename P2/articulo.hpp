//
// Created by poo on 21/4/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_ARTICULO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_ARTICULO_HPP

#include "iomanip"

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo{

    public:
        Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned int existencias = 0);

        // Observadores estándar
        inline const Cadena& referencia() const { return referencia_; };
        inline const Cadena& titulo() const { return titulo_; };
        inline const Fecha& f_publi() const { return publicacion_; };
        inline double precio() const { return precio_; };
        inline unsigned int stock() const { return existencias_; };

        // Observadores/modificadores sobrecargados
        inline double& precio() { return precio_; };
        inline unsigned int& stock() { return existencias_; };

        friend std::ostream& operator << (std::ostream& os, const Articulo& articulo);

    private:

        const Cadena referencia_, titulo_;
        const Fecha publicacion_;
        double precio_;
        unsigned int existencias_;
};

#endif //ALVAREZ_CRUZ_ABRAHAM_ARTICULO_HPP
