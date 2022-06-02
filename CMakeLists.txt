cmake_minimum_required(VERSION 3.21)
project(Alvarez_Cruz_Abraham)

set(CMAKE_CXX_STANDARD 14)

add_executable(Alvarez_Cruz_Abraham
        P3/pedido.cpp P3/pedido.hpp P3/pedido-articulo.cpp P3/pedido-articulo.hpp
        P3/usuario-pedido.cpp P3/usuario-pedido.hpp P3/usuario.hpp P3/usuario.cpp P4/libro-digital.h)
