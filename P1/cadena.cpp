//
// Created by poo on 26/3/22.
//

#include "cadena.hpp"

// --- Cadena::Utilidades ---
Cadena Cadena::Utilidades::vector2Cadena(std::vector<char>& v){
    unsigned int tam = v.size();
    Cadena temp(tam);

    for (int i = 0; i < tam; ++i) {
        temp[i] = v[i];
    }

    return temp;
}
Cadena Cadena::Utilidades::numero2Cadena(int n){

    if (n < 0) throw std::runtime_error("No se puede transformar actualmente");

    std::vector<char> vector{};

    Cadena final{};
    int entera = n;

    while (entera > 0){

    int temp = entera / 10;
    int decimal = entera % 10;
    entera = temp;

    vector.push_back((char) ('0' + decimal));
    }
    std::reverse(vector.begin(), vector.end());
    return vector2Cadena(vector);
}
// --------------------------

// --- Constructores ---
Cadena::Cadena(size_t tamanio, char relleno): tam_(tamanio) {

    // Reservamos memoria para la cadena
    s_ = new char[tam_+1] ;

    // LLenamos la cadena con el caracter de relleno
    for(size_t i = 0 ; i < tamanio ; ++i){
        s_[i] = relleno ;
    }

    // Añadimos el caracter final
    s_[tam_] = '\0' ;
}
Cadena::Cadena(const Cadena &c): tam_(c.tam_){
    s_ = new char[c.tam_ + 1];
    strcpy(s_, c.s_);
}
Cadena::Cadena(const char* a): tam_(strlen(a)) {
    s_ = new char[tam_ + 1];
    strcpy(s_, a);
}
Cadena::Cadena(Cadena&& c2): s_(c2.s_), tam_(c2.tam_) {
    c2.s_ = nullptr;
    c2.tam_ = 0;
}
// ---------------------


//  --- Observadores ---
char Cadena::at(size_t i) const {
    if (i < 0 || tam_ == 0) throw std::out_of_range("Índice no válido");
    return s_[i];
}
char& Cadena::at(size_t i) {
    if (i < 0 || i > tam_ - 1) throw std::out_of_range("Índice no válido");
    return s_[i];
}
Cadena Cadena::substr(unsigned int indx, unsigned int tam) {

    // Comprobamos que esté en un rango válido
    if (indx < 0 || indx > tam_ - 1) throw std::out_of_range("Índice no válido");

    // Calculamos si hay suficientes caracteres
    unsigned int diff = tam_ - indx;
    if (diff < tam) throw std::out_of_range("No hay tanto caracteres");

    Cadena nueva{tam};
    for (unsigned int i = indx; i < indx + tam; ++i) {
        char c = s_[i + indx];
        nueva[i - indx] = s_[i];
    }

    return nueva;
}
Cadena Cadena::substr(unsigned int indx, unsigned int tam) const {
    // Comprobamos que esté en un rango válido
    if (indx < 0 || indx > tam_ - 1) throw std::out_of_range("Índice no válido");

    // Calculamos si hay suficientes caracteres
    unsigned int diff = tam_ - indx;
    if (diff < tam) throw std::out_of_range("No hay tanto caracteres");

    Cadena nueva{tam};
    for (unsigned int i = indx; i < indx + tam; ++i) {
        char c = s_[i + indx];
        nueva[i - indx] = s_[i];
    }

    return nueva;
}
const char *Cadena::c_str() const noexcept {
    return s_;
}
// ---------------------


// --- Operadores ---
Cadena& Cadena::operator=(const Cadena &c2) {

    if (this != &c2){

        // ELiminamos la cadena actual
        delete[] this->s_ ;

        // Reservamos memoria para la nueva cadena y su tamaño
        this->tam_ = strlen(c2.s_) ;
        this->s_ = new char[tam_ +1] ;

        // Copiamos el contenido de la cadena
        strcpy(this->s_,c2.s_) ;
    }

    return *this;
}
Cadena& Cadena::operator=(const char* c2){

    // ELiminamos la cadena actual
    delete[] this->s_ ;

    // Reservamos memoria para la nueva cadena y su tamaño
    this->tam_ = strlen(c2) ;
    this->s_ = new char[tam_ +1] ;

    // Copiamos el contenido de la cadena
    strcpy(this->s_,c2) ;
    return *this;
}
Cadena& Cadena::operator=(Cadena&& c2)  noexcept {

    // Nos asignamos los valores de los atributos de c2
    this->tam_ = c2.tam_;
    this->s_ = c2.s_;

    c2.tam_ = 0;
    c2.s_ = nullptr;        // Importante para evitar errores con nuestra cadena

    return *this;
}
Cadena& Cadena::operator +=(const Cadena& c2){

    char* temp = new char[tam_ + c2.tam_ + 1]();
    strcpy(temp, s_);
    strcat(temp, c2.s_);
    tam_ += c2.tam_;

    delete[] s_;
    s_ = temp;

    return *this;
}
Cadena operator+(const Cadena &c1, const Cadena &c2) {
    return Cadena(c1) += c2;
}
bool operator==(const Cadena &c1, const Cadena &c2) {
    return strcmp(c1.c_str(), c2.c_str()) == 0;
}
bool operator<(const Cadena &c1, const Cadena &c2) {
    return strcmp(c1.c_str(), c2.c_str()) <= -1;
}
bool operator<=(const Cadena &c1, const Cadena &c2) {
    return !(c1 > c2);
}
bool operator>(const Cadena &c1, const Cadena &c2) {
    return strcmp(c1.c_str(), c2.c_str()) >= 1;
}
bool operator>=(const Cadena &c1, const Cadena &c2) {
    return !(c1 < c2);
}
bool operator!=(const Cadena &c1, const Cadena &c2) {
    return !(c1 == c2);
}
char& Cadena::operator[](unsigned int i) {
    return s_[i];
}
const char& Cadena::operator[](unsigned int i) const {
    return s_[i];
}
std::ostream& operator << (std::ostream& s, const Cadena& c){
    return s << c.c_str();
}
std::istream& operator >> (std::istream& s, Cadena& c){

    // Buscamos la primera letra de la linea
    for (int i = 0; i < 32 && isspace(s.peek()); ++i && s.get());

    // Vamos cogiendo los caracteres para formar la palabra
    char* tempString = new char[32];
    int i = 0;
    while(s.good() && !isspace(s.peek()) && i < 32 && s.peek() != EOF){
        tempString[i++] = (char) s.get();
    }
    tempString[i]='\0';                 // Añadimos el caracter final

    // Creamos una cadena con los caracteres justos y copiamos el contenido de la temporal
    char* cadenaFinal = new char[strlen(tempString)];
    strcpy(cadenaFinal, tempString);
    c = Cadena{cadenaFinal};

    // Eliminamos las cadenas temporales
    delete[] tempString;
    delete[] cadenaFinal;

    return s;
}
// -----------------

Cadena::~Cadena() {
    delete[] s_;
}