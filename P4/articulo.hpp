//
// Created by poo on 21/4/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_ARTICULO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_ARTICULO_HPP

#include "iomanip"

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "set"

class Autor {

    public:
        Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept;

        // Observadores
        inline const Cadena& nombre() const { return nombre_; };
        inline const Cadena& apellidos() const { return apellidos_; };
        inline const Cadena& direccion() const { return direccion_; };

    private:
        Cadena nombre_, apellidos_, direccion_;
};

class Articulo{

    public:

        typedef std::set<Autor*> Autores;

        class Autores_vacios {

            public:
                Autores_vacios(const Autores& autores): autores_(autores){};

            private:
                const Autores& autores_;
        };

        Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio);

        // Observadores estándar
        inline const Cadena& referencia() const { return referencia_; };
        inline const Cadena& titulo() const { return titulo_; };
        inline const Fecha& f_publi() const { return publicacion_; };
        inline double precio() const { return precio_; };
        inline const Autores& autores() const { return autores_; };

        // Observadores/modificadores sobrecargados
        inline double& precio() { return precio_; };

        virtual ~Articulo(){};    // Destructor virtual necesario para las clases hijas
        virtual void impresion_especifica(std::ostream& os) const = 0;

    private:

        const Cadena referencia_, titulo_;
        const Fecha publicacion_;
        double precio_;
        Autores autores_;
};

class LibroDigital: public Articulo {

    public:
        LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, const Fecha& expiracion);

        // Observadores
        inline const Fecha& f_expir() const { return expiracion_; };

        virtual void impresion_especifica(std::ostream& os) const;

    private:
        const Fecha expiracion_;

};

class ArticuloAlmacenable: public Articulo{

    public:
        ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned int stock = 0);

        // Observadores
        inline unsigned int stock() const { return stock_; };
        virtual void impresion_especifica(std::ostream& os) const = 0;

        // Modificadores
        inline unsigned int& stock() { return stock_; };

        virtual ~ArticuloAlmacenable(){};

    private:
        unsigned int stock_;
};

class Libro: public ArticuloAlmacenable {

    public:
        Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned int n_pag, unsigned int stock = 0);

        // Observadores
        inline unsigned int n_pag() const { return n_pag_; }
        virtual void impresion_especifica(std::ostream& os) const;

    private:
        unsigned int n_pag_;
};

class Cederron: public ArticuloAlmacenable {

    public:
        Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned int tam, unsigned int stock = 0);

        // Observadores
        inline unsigned int tam() const { return tam_; };

        virtual void impresion_especifica(std::ostream& os) const;

    private:
        unsigned int tam_;
};

std::ostream& operator << (std::ostream& os, const Articulo& articulo);

#endif //ALVAREZ_CRUZ_ABRAHAM_ARTICULO_HPP
