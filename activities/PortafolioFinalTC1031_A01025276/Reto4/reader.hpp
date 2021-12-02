#ifndef reader_hpp 
#define reader_hpp
#include <string>
#include "registry.hpp"
#include <fstream>
#include <vector>

using namespace std;

class Reader{
    public: 
    Reader() = default; 
    ~Reader() = default;
    
    vector<Registry> readFile(){
        ifstream ip("equipo5.csv");
        vector<Registry> registros; 
        
        if(!ip.is_open()){
           std::cout << "Error: File Open" << endl; 
        }

        string fecha; 
        string hora; 
        string fuente_ip; 
        string fuente_puerto; 
        string fuente_hostname; 
        string destino_ip; 
        string destino_puerto; 
        string destino_hostname;

        while(ip.good()){
            getline(ip, fecha, ','); 
            getline(ip, hora, ',');
            getline(ip, fuente_ip, ',');
            getline(ip, fuente_puerto, ',');
            getline(ip, fuente_hostname, ',');
            getline(ip, destino_ip, ',');
            getline(ip, destino_puerto, ',');
            getline(ip, destino_hostname, '\n');
             registros.push_back(Registry(fecha,hora, fuente_ip, fuente_puerto, fuente_hostname, destino_ip, destino_puerto, destino_hostname)); 
        }

        ip.close(); 
        return registros; 
    }
};

#endif