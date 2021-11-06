#ifndef compConnections_h 
#define compConnections_h
#include <string>
#include <stack>
#include <queue>
#include "connection.hpp"
#include <iostream>

class CompConnections{
    public:        
        std::string ip;
        std::string name;
        std::stack<Connection> inConnections; 
        std::queue<Connection> outConnections; 

        CompConnections(std::string IP, std::string name){
            this -> ip = IP;
            this -> name = name; 
        };
        
        ~CompConnections() {}; 

        void addToIncomingConnections(std::string IP, int port, std::string host){
            Connection c(IP, port, host);
            inConnections.push(c);
        }

        void addToOutgoingConnections(std::string IP, int port, std::string host){
            Connection c(IP, port, host); 
            outConnections.push(c);
        }
};

#endif

