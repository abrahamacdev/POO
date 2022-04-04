#include <sstream>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

int main() {

    istringstream is("prueba");
    Cadena c;
    is >> c;

    cout << c << endl;

    return 0;
}
