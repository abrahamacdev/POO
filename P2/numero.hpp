//
// Created by poo on 21/4/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_NUMERO_HPP
#define ALVAREZ_CRUZ_ABRAHAM_NUMERO_HPP

#include "../P1/cadena.hpp"

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

#endif //ALVAREZ_CRUZ_ABRAHAM_NUMERO_HPP
