#ifndef connection_h 
#define connection_h
#include <string>

/*
Class to create a conection between machines
*/
class Connection{
    public:
        std::string ip;
        int port;
        std::string host;

        Connection(){}

        Connection(std::string IP, int port, std::string host){
            this -> ip = IP;
            this -> port = port;
            this -> host = host;
        }

        ~Connection() {};
}; 

#endif