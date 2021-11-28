#ifndef compConnections_hpp 
#define compConnections_hpp
#include <string>
#include <list>
#include "connection.hpp"
#include "registry.hpp"
#include <vector>
#include <iostream>

class CompConnections{
    public:
        CompConnections(std::string IP, std::string name){
            this->IP = IP;
            this->name = name; 
        };

        CompConnections(){
            this->IP = "";
            this->name = "";
        };
        
        ~CompConnections() {}; 

        std::string IP;
        std::string name;
        std::list<Connection> inConnections; //leer de última a primera
        std::list<Connection> outConnections; //leer de primera a última

        void insertToInConnections(std::string IP, int port, std::string host, tm date){
            Connection c(IP, port, host, date);
            inConnections.push_front(c);
        }

        void insertToOutConnections(std::string IP, int port, std::string host, tm date){
            Connection c(IP, port, host, date); 
            outConnections.push_back(c);
        }

        std::string lastInConnection(){
            return inConnections.front().getIP(); 
        }

        void fill(std::vector <Registry> datos){
            for (int i = 0; i < datos.size(); i++){
                if (datos[i].destinationIp == this->IP ){
                    this->insertToInConnections(
                        datos[i].sourceIp, 
                        datos[i].sourcePort,
                        datos[i].sourceName,
                        datos[i].date
                    );
                } 

                if (datos[i].sourceIp == this->IP ){
                    this->insertToOutConnections(
                        datos[i].destinationIp, 
                        datos[i].destinationPort,
                        datos[i].destinationName,
                        datos[i].date
                    );
                } 
            }
        }
};

#endif