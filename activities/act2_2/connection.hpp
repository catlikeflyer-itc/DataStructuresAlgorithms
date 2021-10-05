#ifndef connection_h 
#define connection_h
#include <string>

/*
Class to create a conection between machines
*/
class Connection{
    public:
        Connection(std::string IP, int port, std::string host){
            this -> ip = IP;
            this -> port = port;
            this -> host = host;
        }
        ~Connection() {}; 
        std::string ip;
        int port;
        std::string host;

        std::string getIP(){
            return ip; 
        }
}; 

#endif