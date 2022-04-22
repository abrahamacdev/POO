//
// Created by poo on 21/4/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_USUARIO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_USUARIO_HPP

#include "map"
#include "unordered_map"
#include "unordered_set"
#include "articulo.h"
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "numero.hpp"
#include "clave.hpp"
#include "iostream"

class Usuario {
public:
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;
    typedef std::map<Numero, Tarjeta*> Tarjetas;

    class Id_duplicado {
        const Cadena identificador;

        public:
            explicit Id_duplicado(const Cadena& id): identificador(id){};
            inline const Cadena& idd() const { return identificador; }
    };

    Usuario(const Cadena& identificador, const Cadena& nombre,
            const Cadena& apellidos, const Cadena& direccion, const Clave& clave);

    // "Un Usuario no podrá crearse por copia de otro ni asignarse"
    Usuario(const Usuario& u) = delete;
    Usuario& operator=(const Usuario& u) = delete;

    // Asociacion con clase Tarjeta
    void es_titular(Tarjeta& tarjeta);
    void no_es_titular_de(Tarjeta& tarjeta);

    // Asociacion con la clase Articulo
    void compra(Articulo& articulo, unsigned int cantidad = 1);

    // Observadores
    inline const Cadena& id() const { return identificador_; };
    inline const Cadena& nombre() const { return nombre_; };
    inline const Cadena& apellidos() const { return apellidos_; };
    inline const Cadena& direccion() const { return direccion_; };
    //tarjetas() const;                 // TODO Falta añadir el método observador "tarjetas"
    inline const Articulos& compra() const { return carrito; };
    inline size_t n_articulos() const { return carrito.size(); };

    // Operadores
    friend std::ostream& operator << (std::ostream& os, const Usuario& usuario);  // Todo Falta implementar el método

    ~Usuario();

private:

    const Cadena identificador_, nombre_, apellidos_, direccion_;
    const Clave clave_;
    Articulos carrito;
    Tarjetas tarjetas;

    // LLevamos el registro de usuarios
    typedef std::unordered_set<Cadena> Usuarios;
    static Usuarios listadoUsuarios;
};

void mostrar_carro(std::ostream& os, const Usuario& usuario);

#endif //ALVAREZ_CRUZ_ABRAHAM_USUARIO_HPP
