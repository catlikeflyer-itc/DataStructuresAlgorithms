#ifndef connection_hpp 
#define connection_hpp
#include <string>

using namespace std;

class Connection{
    public:
        Connection(std::string IP, int port, std::string host){
            this->IP = IP;
            this->port = port;
            this->host = host;
        }
        Connection(std::string IP, int port, std::string host, tm date){
            this->IP = IP;
            this->port = port;
            this->host = host;
            this->date = date;
        }
        ~Connection() {}; 

        std::string IP;
        int port;
        std::string host;
        tm date;

        std::string getIP(){
            return IP; 
        }
        void printDate(){
            cout << this->date.tm_mday << "/" << this->date.tm_mon+1 << "/" << this->date.tm_year+1900;
        }
}; 

#endif