#ifndef registro_hpp
#define registro_hpp
#include <ctime>
#include <string>
using namespace std;
class Registro{
    public:
        Registro(
            string fecha, 
            string hora, 
            string ip_fuente,
            string puerto_fuente, 
            string hostname_fuente,
            string ip_destino, 
            string puerto_destino, 
            string hostname_destino
        );
        Registro();
        // ~Registro();
        tm fecha; 
        string fechaString;
        string hora; 
        string fuente_ip; 
        int fuente_puerto; 
        // string fuente_puerto; 
        string fuente_hostname; 
        string destino_ip; 
        int destino_puerto; 
        // string destino_puerto; 
        string destino_hostname; 
        void print();
        void printDate();
};
Registro::Registro(
    string _fecha, 
    string _hora, 
    string _fuente_ip,
    string _fuente_puerto, 
    string _fuente_hostname,
    string _destino_ip, 
    string _destino_puerto,
    string _destino_hostname
){
    struct tm tm;
    const char *f = _fecha.c_str();
    strptime(f, "%d-%m-%y", &this->fecha);
    this->fechaString = _fecha;
    this->hora = _hora;
    this->fuente_ip = _fuente_ip;
    this->fuente_hostname = _fuente_hostname;
    this->destino_ip = _destino_ip;
    this->destino_hostname = _destino_hostname;

    try{
        this->fuente_puerto = stoi(_fuente_puerto, nullptr, 10);
        this->destino_puerto = stoi(_destino_puerto, nullptr, 10);
    }catch(...){
        this->fuente_puerto = -1;
        this->destino_puerto = -1;
    }
    // TODO: Convertir a ints
};
void Registro::print(){
    this->printDate();
    cout<<"\t"<<this->hora
    <<"\t"<<this->fuente_ip
    <<"\t"<<this->fuente_puerto 
    <<"\t"<<this->fuente_hostname
    <<"\t"<<this->destino_ip
    <<"\t"<<this->destino_puerto
    <<"\t"<<this->destino_hostname
    <<endl<<"========================"<<endl;
    // cout<<"🐱‍💻"<<endl<<"==============="<<endl;
}
void Registro::printDate(){
    cout<<this->fecha.tm_mday<<"/"<<this->fecha.tm_mon+1<<"/"<<this->fecha.tm_year+1900;
}
#endif