//
// Created by poo on 22/4/22.
//

#include "clave.hpp"

using namespace std;

int main(){

    Clave c("Ejemplo");

    cout << c.clave() << endl;
    cout << c.verifica("Ejemplo") << endl;
}