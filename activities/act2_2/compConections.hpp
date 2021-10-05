#ifndef compConnections_h 
#define compConnections_h
#include <string>
#include <list>
#include "connection.hpp"
#include <iostream>

class CompConnections{
    public:
        CompConnections(std::string IP, std::string name){
            this -> ip = IP;
            this -> name = name; 
        };
        ~CompConnections() {}; 
        std::string ip;
        std::string name;
        std::list<Connection> inConnections; 
        std::list<Connection> outConnections; 

        void addToIncomingConnections(std::string IP, int port, std::string host){
            Connection c(IP, port, host);
            inConnections.push_front(c);
        }

        void addToOutgoingConnections(std::string IP, int port, std::string host){
            Connection c(IP, port, host); 
            outConnections.push_back(c);
        }

        std::string lastIncomingConnection(){
            return inConnections.front().getIP(); 
        }
};
#endif

