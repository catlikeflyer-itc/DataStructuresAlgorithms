#ifndef compConnections_hpp 
#define compConnections_hpp
#include <string>
#include <list>
#include "connection.hpp"
#include <iostream>

class ConexionesComputadora{
    public:
        ConexionesComputadora(std::string IP, std::string nombre){
            this->IP = IP;
            this->nombre = nombre; 
        };
        ConexionesComputadora(){
            this->IP="";
            this->nombre="";
        };
        ~ConexionesComputadora() {}; 
        std::string IP;
        std::string nombre;
        std::list<Conexion> conexionesEntrantes; //leer de última a primera
        std::list<Conexion> conexionesSalientes; //leer de primera a última

        void insertarEnConexionesEntrantes(std::string IP, int puerto, std::string host, tm fecha){
            Conexion c(IP, puerto, host, fecha);
            conexionesEntrantes.push_front(c);
        }

        void insertarEnConexionesSalientes(std::string IP, int puerto, std::string host, tm fecha){
            Conexion c(IP, puerto, host, fecha); 
            conexionesSalientes.push_back(c);
        }

        std::string ultimaConexionEntrante(){
            return conexionesEntrantes.front().getIP(); 
        }

        void llenar(vector <Registro> datos){
            for(int i=0; i<datos.size(); i++){
                if( datos[i].destino_ip == this->IP ){
                    this->insertarEnConexionesEntrantes(
                        datos[i].fuente_ip, 
                        datos[i].fuente_puerto,
                        datos[i].fuente_hostname,
                        datos[i].fecha
                    );
                } 

                if( datos[i].fuente_ip == this->IP ){
                    this->insertarEnConexionesSalientes(
                        datos[i].destino_ip, 
                        datos[i].destino_puerto,
                        datos[i].destino_hostname,
                        datos[i].fecha
                    );
                } 
            }
        }
};
#endif