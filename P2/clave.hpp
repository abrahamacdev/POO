//
// Created by poo on 21/4/22.
//

#ifndef ALVAREZ_CRUZ_ABRAHAM_CLAVE_HPP
#define ALVAREZ_CRUZ_ABRAHAM_CLAVE_HPP

#include "../P1/cadena.hpp"

class Clave {

    public:
        enum Razon {
            CORTA,
            ERROR_CRYPT
        };

        class Incorrecta {

            Razon razon_;

            public:
                explicit Incorrecta(const Razon r): razon_(r){};

                inline const Razon& razon() const { return razon_; };
        };

        explicit Clave(const char* contrasenia);

        bool verifica(const char* c) const;
        inline const Cadena& clave() const { return contrasenia_; };

    private:
        Cadena contrasenia_;
        static const int tamanioSalt_ = 2;
};

#endif //ALVAREZ_CRUZ_ABRAHAM_CLAVE_HPP
