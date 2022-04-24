//
// Created by poo on 22/4/22.
//

#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "clave.hpp"

using namespace std;

int main(){

    const char* contrasenia_plana = "Ejemplo";

    // Contrasenia que tendremos para el usuario
    Clave clave = Clave(contrasenia_plana);

    // Creamos el usuario
    Usuario abraham{"abraham", "Abraham", "Álvarez Cruz", "Calle Sol nº4", clave};

    cout << "(Antes de añadir productos)" << endl;
    cout << "Tenemos en el carrito " << abraham.n_articulos() << " artículos distintos y nuestra clave es \'" << clave.clave() << "\'" << endl;

    Articulo rust{"110", "Fundamento de Rust", Fecha(23, 2, 2022), 20.044, 5};
    cout << rust << endl;


    abraham.compra(rust, 2);
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "(Después de añadir productos)" << endl;
    mostrar_carro(cout, abraham);
}