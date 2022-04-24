//
// Created by poo on 22/4/22.
//

#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include "articulo.hpp"

using namespace std;

int main(){

    const char* contrasenia_plana = "Ejemplo";

    // Contrasenia que tendremos para el usuario
    Clave clave = Clave(contrasenia_plana);

    // Creamos el usuario
    Usuario abraham{"abraham", "Abraham", "Álvarez Cruz", "Calle Sol nº4", clave};

    /*Numero n("4548812049400004");
    Tarjeta t{n, abraham, Fecha(20, 7, 2022)};*/

    const char* vacio = abraham.compra().empty() ? "Vacío" : "Con cosas";

    Articulo rust{"110", "Fundamento de Rust", Fecha(23, 2, 2022), 20.044, 5};
    Articulo go{"129", "Fundamento de Go", Fecha(23, 2, 2022), 25.049, 2};
    //cout << rust << endl;

    abraham.compra(rust);
    abraham.compra(go, 7);


    cout << std::setfill('*') << setw(30) << "" << endl;
    mostrar_carro(cout, abraham);
}