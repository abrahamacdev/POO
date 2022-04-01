cmake_minimum_required(VERSION 3.21)
project(Alvarez_Cruz_Abraham)

set(CMAKE_CXX_STANDARD 14)

include_directories(P0)

add_executable(Alvarez_Cruz_Abraham
        P0/cadena.hpp
        P0/fecha.hpp
        P0/main.cpp P0/fecha.hpp P0/cadena.hpp P0/cadena.cpp P0/fecha.cpp)
