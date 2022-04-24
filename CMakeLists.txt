cmake_minimum_required(VERSION 3.21)
project(Alvarez_Cruz_Abraham)

set(CMAKE_CXX_STANDARD 14)

include_directories(P0)

add_executable(Alvarez_Cruz_Abraham
        luhn.cpp
        P0/cadena.hpp
        P0/fecha.hpp
        P0/main.cpp P0/fecha.hpp P0/cadena.hpp P0/cadena.cpp P0/fecha.cpp
        P1/cadena.hpp
        P1/fecha.hpp
        P1/main.cpp P1/fecha.hpp P1/cadena.hpp P1/cadena.cpp P1/fecha.cpp
        P2/usuario.cpp P2/usuario.hpp P2/articulo.cpp P2/articulo.hpp P2/tarjeta.cpp P2/tarjeta.hpp P2/numero.cpp P2/numero.hpp
        P2/clave.cpp P2/clave.hpp P2/main.cpp)
