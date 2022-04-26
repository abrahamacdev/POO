//
// Created by poo on 21/4/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_TARJETA_HPP
#define ALVAREZ_CRUZ_ABRAHAM_TARJETA_HPP

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

#include "usuario.hpp"

class Usuario;

class Numero {

public:
    enum Razon {
        LONGITUD, DIGITOS, NO_VALIDO
    };

    class Incorrecto {

        Razon razon_;

    public:
        explicit Incorrecto(Razon razon): razon_(razon){};

        const Razon& razon() const { return razon_; };
    };

    // Contructores
    explicit Numero(const Cadena& numero);

    // Operadores
    operator const char*() const;

    friend bool operator <(const Numero& numero1, const Numero& numero2);

private:
    Cadena numero_;
};

class Tarjeta{

    public:
        enum Tipo {
            Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress
        };

        class Caducada {
            const Fecha caducada_;

            public:
                Caducada(const Fecha& caducada): caducada_(caducada){};

                inline const Fecha& cuando() const { return caducada_; };
        };
        class Num_duplicado{

            const Numero numero_;

            public:
                Num_duplicado(const Numero& numero): numero_(numero){};
                inline const Numero& que() const { return numero_; }
        };
        class Desactivada {};


        Tarjeta(const Numero& numeroTarjeta, const Usuario& titular, const Fecha& caducidad);

        // "Dos tarjetas_ no se pueden copiar, ni al crearse ni por asignación"
        Tarjeta(const Tarjeta&) = delete;
        Tarjeta& operator = (const Tarjeta&) = delete;

        inline const Numero& numero() const { return numeroTarjeta_; }
        inline const Usuario* titular() const { return titular_; }
        inline const Fecha& caducidad() const { return caducidad_; }
        inline bool activa() const { return activa_; }
        Tipo tipo() const;

        bool activa(bool activar = true);
        void anula_titular();

        ~Tarjeta();

        friend std::ostream& operator << (std::ostream& os, const Tarjeta& tarjeta);

        friend bool operator <(const Tarjeta& t1, const Tarjeta& t2);


    private:
        const Numero numeroTarjeta_;
        const mutable Usuario* titular_;
        const Fecha caducidad_;
        bool activa_;

};

std::ostream& operator << (std::ostream& os, const Tarjeta::Tipo& tipo);

#endif //ALVAREZ_CRUZ_ABRAHAM_TARJETA_HPP
