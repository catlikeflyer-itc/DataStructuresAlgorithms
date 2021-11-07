#ifndef connection_hpp 
#define connection_hpp
#include <string>

class Conexion{
    public:
        Conexion(std::string IP, int puerto, std::string host){
            this->IP = IP;
            this->puerto = puerto;
            this->host = host;
        }
        Conexion(std::string IP, int puerto, std::string host, tm fecha){
            this->IP = IP;
            this->puerto = puerto;
            this->host = host;
            this->fecha = fecha;
        }
        ~Conexion() {}; 
        std::string IP;
        int puerto;
        std::string host;
        tm fecha;
        std::string getIP(){
            return IP; 
        }
        void imprimirFecha(){
            std::cout<<this->fecha.tm_mday<<"/"<<this->fecha.tm_mon+1<<"/"<<this->fecha.tm_year+1900;
        }
}; 

#endif

