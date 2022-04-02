//
// Created by Judith Olalde Alonso on 6/3/22.
//

//
// Created by abrah on 26/02/2022.
//

#ifndef FECHA_CADENA_HPP
#define FECHA_CADENA_HPP

#include "cstring"
#include "vector"
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "iostream"
#include "iterator"

class Cadena {

    char* s_;
    size_t tam_;

public:

    // Constructores
    explicit Cadena(size_t tamanio = 0, char relleno = ' ');    // Cto defecto, 1 párametro y 2 parámetros
    Cadena(const Cadena& c);                                    // Cto copia
    Cadena(const char* a);                                      // Cto cadena
    Cadena(Cadena&& c);                                         // Cto de movimiento


    // Observadores
    inline size_t length() const noexcept { return tam_; };
    char at(size_t i) const;
    char& at(size_t i);
    Cadena substr(unsigned int indx, unsigned int tam);
    Cadena substr(unsigned int indx, unsigned int tam) const;
    const char* c_str() const noexcept;


    // Operadores
    Cadena& operator =(const Cadena& c2);
    Cadena& operator =(const char* c2);
    Cadena& operator =(Cadena&& c2) noexcept;
    Cadena& operator +=(const Cadena& c2);
    char& operator[](unsigned int i);
    const char& operator[](unsigned int i) const;

    // Iteradores
    typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator ;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator ;

	iterator begin() { return s_ ;}                                         // "Normales"
    iterator end() { return s_ + tam_ ; }
	const_iterator begin() const { return cbegin();  }                      // "Normal" (instancia constante)
    const_iterator end() const {return cend(); }
	const_iterator cbegin() const { return s_;}                             // Constantes
    const_iterator cend() const { return s_ + tam_ ; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }           // Reverso
    reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rbegin() const { return crbegin(); }             // Reverso (instancia constante)
    const_reverse_iterator rend() const { return crend(); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }        // Reverso constante
	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    ~Cadena();

    class Utilidades {

    public:

        static Cadena vector2Cadena(std::vector<char>& v);
        static Cadena numero2Cadena(int n);
    };
};

Cadena operator+(const Cadena& cad1, const Cadena& cad2)  ;
bool operator <(const Cadena& f1 , const Cadena& f2) ;
bool operator >(const Cadena& f1 , const Cadena& f2) ;
bool operator !=(const Cadena& f1 , const Cadena& f2) ;
bool operator <=(const Cadena& f1 , const Cadena& f2) ;
bool operator >=(const Cadena& f1 , const Cadena& f2) ;
bool operator ==(const Cadena& f1 , const Cadena& f2) ;
std::istream& operator >> (std::istream& s, Cadena& c);
std::ostream& operator << (std::ostream& s, const Cadena& c);

#endif //FECHA_CADENA_HPP