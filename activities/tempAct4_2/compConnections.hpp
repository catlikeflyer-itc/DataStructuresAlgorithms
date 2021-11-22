#ifndef compConnections_hpp 
#define compConnections_hpp
#include <string>
#include <list>
#include <vector>
#include "connection.hpp"
#include "registry.hpp"
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

        void fill(std::vector<Registry> data){
            for(int i=0; i<data.size(); i++){
                if (data[i].destinationIp == this->IP){
                    this->insertToInConnections(
                        data[i].sourceIp, 
                        data[i].sourcePort,
                        data[i].sourceName,
                        data[i].date
                    );
                } 

                if (data[i].sourceIp == this->IP ){
                    this->insertToOutConnections(
                        data[i].destinationIp, 
                        data[i].destinationPort,
                        data[i].destinationName,
                        data[i].date
                    );
                } 
            }
        }
};

#endif