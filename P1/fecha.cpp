//
// Created by poo on 26/3/22.
//

#include "./fecha.hpp"

// --- Fecha::Utilidades ---
int Fecha::Utilidades::diaActual(){
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    return tiempo_descompuesto->tm_mday;
}
int Fecha::Utilidades::mesActual(){
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    return tiempo_descompuesto->tm_mon + 1;
}
int Fecha::Utilidades::anioActual(){
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    return tiempo_descompuesto->tm_year + 1900;
}
int Fecha::Utilidades::maxDiaDelMes(int m, int y){
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 31;
    else if(m == 4 || m == 6 || m == 9 || m == 11) return 30;
    else {
        if(y % 4 == 0) {
            if(y % 100 == 0) {
                if(y % 400 == 0) return 29;
                return 28;
            }
            return 29;
        }
        return 28;
    }
}
const char* Fecha::Utilidades::mes2Texto(int m){
    switch (m) {
    case 1:
    return "enero";
    case 2:
    return "febrero";
    case 3:
    return "marzo";
    case 4:
    return "abril";
    case 5:
    return "mayo";
    case 6:
    return "junio";
    case 7:
    return "julio";
    case 8:
    return "agosto";
    case 9:
    return "septiembre";
    case 10:
    return "octubre";
    case 11:
    return "noviembre";
    case 12:
    return "diciembre";
    default:
    return "";
    }
}
const char* Fecha::Utilidades::diaSemana2Texto(const Fecha& f){
    struct tm expire_time = {};
    expire_time.tm_year = f.anio_ - 1900;
    expire_time.tm_mon = f.mes_ - 1;
    expire_time.tm_mday = f.dia_;

    time_t tempTime = mktime(&expire_time);
    const std::tm * time_out = std::localtime(&tempTime);

    int diaSemana = time_out->tm_wday;

    switch (diaSemana) {
        case 0:
        case 7:
            return "domingo";

        case 1:
            return "lunes";

        case 2:
            return "martes";

        case 3:
            return "miércoles";

        case 4:
            return "jueves";

        case 5:
            return "viernes";

        case 6:
            return "sábado";

        default:
            return "";
    }
}
// -------------------------

// --- Fecha::Invalida ---
Fecha::Invalida::Invalida(): porque("Ni idea"){};
Fecha::Invalida::Invalida(const char *p): porque(p){};
const char *Fecha::Invalida::por_que() const {
    return porque;
}
const char *Fecha::Invalida::what() const throw() {
    return porque;
}
// -----------------------


// --- Constructores ---
Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anio_(a) {
    validar();
}

Fecha::Fecha(const char* f) {

    int dia, mes, anio;

    if(sscanf(f, "%d/%d/%d", &dia, &mes, &anio) != 3) throw Fecha::Invalida("Fecha incorrecta");
    else{
        dia_ = dia;
        mes_ = mes;
        anio_ = anio;

        validar();
    }
}

void Fecha::validar() {

    // Comprobamos que el mes_ sea válido
    if (mes_ == 0) mes_ = Fecha::Utilidades::mesActual();
    else if (!mesValido(mes_)) throw Invalida{"Mes no válido"};

    // Comprobamos que el año sea válido
    if (anio_ == 0) anio_ = Fecha::Utilidades::anioActual();
    else if (!anioValido(anio_)) throw Invalida{"Año no válido"};

    // Comprobamos que el día sea válido
    if (dia_ == 0) dia_ = Fecha::Utilidades::diaActual();
    else if (!diaValido(dia_,mes_,anio_)) throw Invalida{"Día no válido"};
}
// ---------------------


// --- Auxiliar ---
void Fecha::imprimir() const noexcept{

    Cadena d{2}, m{2}, a{};

    if (dia_ < 10){
        d[0] = '0';
        d[1] = (char) dia_;
    }
    else d[1] = (char) dia_;

    if (mes_ < 10){
        m[0] = '0';
        m[1] = (char) mes_;
    }
    else m[1] = (char) mes_;

    a = std::to_string(anio_).c_str();

    std::cout << d << "/" << m << "/" << a << std::endl;
}

bool Fecha::diaValido(int d, int m, int y){
    // Día >= 1 && <= 28|29|30|31
    return d > 0 && d <= Fecha::Utilidades::maxDiaDelMes(m, y);
}

bool Fecha::mesValido(int m) {
    // Mes >= 1 && <= 12;
    return m > 0 && m < 13;
}

bool Fecha::anioValido(int a) {
    return a >= Fecha::AnnoMinimo && a <= Fecha::AnnoMaximo;
}

Cadena Fecha::dia2Cadena() const{
    if (dia_ < 10){
        Cadena temp{1};
        temp[0] = '0' + dia_;
        return temp;
    }
    else {
        char* numberstring = (char *) malloc((sizeof (int )) * INT16_MAX);
        sprintf(numberstring, "%d", dia_);
        Cadena temp = Cadena{numberstring};
        free(numberstring);
        return temp;
    }
}
Cadena Fecha::anio2Cadena() const{
    return Cadena{std::to_string(anio_).c_str()};
}
// -----------------


// --- Operadores ---
Fecha Fecha::operator+(int d) {
    return Fecha(*this) += d;
}
Fecha Fecha::operator+(int d) const {
    return Fecha(*this) += d;
}
Fecha Fecha::operator-(int d) {
    return Fecha(*this) -= d;
}
Fecha Fecha::operator-(int d) const {
    return Fecha(*this) -= d;
}
Fecha& Fecha::operator+=(int d) {

    struct tm fechaTM = {};
    fechaTM.tm_year = anio_ - 1900;
    fechaTM.tm_mon = mes_ - 1;
    fechaTM.tm_mday = dia_ + d;

    mktime(&fechaTM);

    dia_ = fechaTM.tm_mday;
    mes_ = fechaTM.tm_mon + 1;
    anio_ = fechaTM.tm_year + 1900;

    validar();

    return *this;
}
Fecha& Fecha::operator-=(int d) {
    *this += -d;
    return *this;
}
Fecha Fecha::operator++(int d) {
    Fecha tmp(*this);
    *this += 1;
    return tmp;
}
Fecha Fecha::operator--(int d) {
    Fecha tmp(*this);
    *this += -1;
    return tmp;
}
Fecha& Fecha::operator++() {
    return *this += 1;
}
Fecha& Fecha::operator--() {
    return  *this -= 1;
}
bool operator==(const Fecha& f1, const Fecha& f2) {
    return f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() == f2.dia();
}
bool operator<(const Fecha& f1, const Fecha& f2) {

    // Comparamos los años
    if (f1.anno() > f2.anno()) return false;       // Nuestro año es mayor que el otro
    else if (f1.anno() < f2.anno()) return true;   // Su año es mayor que el nuestro
    else {                                  // Tenemos el mismo año

        // Comparamos los años
        if (f1.mes() > f2.mes()) return false;     // Nuestro mes_ es mayor que el otro
        else if (f1.mes() < f2.mes()) return true; // Su mes_ es mayor que el nuestro
        else {                              // Tenemos el mismo mes_

            // Comparamos los días
            return f1.dia() < f2.dia();
        }
    }
}
bool operator>(const Fecha& f1, const Fecha& f2) {
    /*if(f1.anno() > f2.anno()) return true;
    else if (f1.anno() == f2.anno()){
        if (f1.mes() > f2.mes()) return true;
        else if (f1.mes() == f2.mes() && f1.dia() > f2.dia()) return true;
    }*/
    return !(f1 < f2) && !(f1 == f2);
}
bool operator<=(const Fecha& f1, const Fecha &f2)  {
    return !(f1 > f2);
}
bool operator>=(const Fecha& f1, const Fecha &f2) {
    return !(f1 < f2);
}
bool operator!=(const Fecha& f1, const Fecha &f2) {
    return !(f1 == f2);
}
std::ostream& operator <<(std::ostream& s, const Fecha& f){
    return s << f.cadena();
}
std::istream& operator >>(std::istream& s, Fecha& f){

    // Leemos 11 caracteres del flujo
    char* sTemporal = new char[11];
    s.getline(sTemporal, 11);

    try {

        f = Fecha{sTemporal};

    }catch (Fecha::Invalida& f){

        // Marcamos el flujo de entrada con el estado de fallo (fail) y propagamos el error
        s.setstate(std::ios_base::failbit);
        delete[] sTemporal;
        sTemporal = nullptr;
        throw f;
    }

    delete[] sTemporal;


    return s;
}
// ------------------


// --- Observadores ---
const char* Fecha::cadena() const noexcept {

    static char f[40];
    sprintf(f, "%s %d de %s de %d", Fecha::Utilidades::diaSemana2Texto(*this), dia_, Fecha::Utilidades::mes2Texto(mes_), anio_);

    return f;
}
// ------------------