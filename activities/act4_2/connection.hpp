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
        std::string date;

        Connection(){}

        Connection(std::string IP, int port, std::string host){
            this -> ip = IP;
            this -> port = port;
            this -> host = host;
        }

        Connection(std::string IP, int puerto, std::string host, std::string date){
            this->ip = IP;
            this->port = puerto;
            this->host = host;
            this->date = date;
        }

        ~Connection() {};

        std::string getIP(){
            return ip; 
        }
        /* void imprimirFecha(){
            std::cout << this -> date.tm_mday << "/" << this -> date.tm_mon+1 << "/" << this -> date.tm_year+1900;
        } */
}; 

#endif