#include "data.hpp"

// definition of setter/getter methods
void Data::setFecha(std::string _fecha){
    fecha = Data::splitter(_fecha, "-");
}

std::vector<std::string> Data::getFecha(){
    return fecha;
}

void Data::setHora(std::string _hora){
    hora = _hora;
}

std::string Data::getHora(){
    return hora;
}

void Data::setIPO(std::string _ip_o){
    ip_o = _ip_o;
}

std::string Data::getIPO(){
    return ip_o;
}

void Data::setPuertoO(std::string _puerto_o){
    puerto_o = _puerto_o;
}

std::string Data::getPuertoO(){
    return puerto_o;
}

void Data::setNombreO(std::string _nombre_o){
    nombre_o = Data::splitter(_nombre_o,".");
}

std::vector<std::string> Data::getNombreO(){
    return nombre_o;
}

void Data::setIPD(std::string _ip_d){
    ip_d = _ip_d;
}

std::string Data::getIPD(){
    return ip_d;
}

void Data::setPuertoD(std::string _puerto_d){
    puerto_d = _puerto_d;
}

std::string Data::getPuertoD(){
    return puerto_d;
}

void Data::setNombreD(std::string _nombre_d){
    nombre_d = _nombre_d;
}

std::string Data::getNombreD(){
    return nombre_d; 
}

// splits a string, returns a vector<string>. In the case of fecha, returns in the format [dd,mm,yy]
std::vector<std::string> Data::splitter(std::string s, std::string del = " "){
    std::vector<std::string> data;    

    int start = 0; // starts at looking for words at char 0
    int end = s.find(del); // ends looking when it encounters char "-"

    while (end != -1) { // loop to repeat the search, adding the resulting string into the return vector
        data.push_back(s.substr(start, end - start));
        start = end + del.size(); // moves the start of the search to after the found "-" char
        end = s.find(del, start);
    }

    data.push_back(s.substr(start, end - start));
    return data;
}

// overloading operator < : fecha
bool Data::operator<(Data const &d){
    if(stoi(fecha[2]) < stoi(d.fecha[2])){ // checks if first object's year is lower than the second's
        return true;
    }
    else if(stoi(fecha[2]) == stoi(d.fecha[2]) && stoi(fecha[1]) < stoi(d.fecha[1])){ // checks if first object's month is lower than the second's, in the case the year is the same
        return true;
    }
    else if(stoi(fecha[2]) == stoi(d.fecha[2]) && stoi(fecha[1]) == stoi(d.fecha[1]) && stoi(fecha[0]) < stoi(d.fecha[0])){ // checks if first object's day is lower than the second's, in the case the year and month are the same
        return true;
    }

    return false;
}

// overloading operator == : nombre_o
bool Data::operator==(Data const &d){
    if(nombre_o[0] == d.nombre_o[0]){
        return true;
    }

    return false;
}