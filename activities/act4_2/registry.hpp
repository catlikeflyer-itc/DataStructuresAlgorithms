#ifndef registry_hpp
#define registry_hpp
//#include <ctime>
#include <string>

class Registry{
    public:
        Registry(
            std::string date, 
            std::string hour, 
            std::string sourceIp,
            std::string sourcePort, 
            std::string sourceName,
            std::string destinationIp, 
            std::string destinationPort, 
            std::string destinationName
        );

        Registry();

        tm date; 
        std::string dateString;
        std::string hour; 
        std::string sourceIp; 
        int sourcePort; 
        std::string sourceName; 
        std::string destinationIp; 
        int destinationPort; 
        std::string destinationName; 

        void print();
        void printDate();
};

Registry::Registry(
    std::string _date, 
    std::string _hour, 
    std::string _sourceIp,
    std::string _sourcePort, 
    std::string _sourceName,
    std::string _destinationIp, 
    std::string _destinationPort,
    std::string _destinationName
){
    struct tm tm;
    const char *f = _date.c_str();
    strptime(f, "%d-%m-%y", &this -> date);
    this -> dateString = _date;
    this -> hour = _hour;
    this -> sourceIp = _sourceIp;
    this -> sourceName = _sourceName;
    this -> destinationIp = _destinationIp;
    this -> destinationName = _destinationName;

    try {
        this -> sourcePort = stoi(_sourcePort, nullptr, 10);
        this -> destinationPort = stoi(_destinationPort, nullptr, 10);
    } catch(...){
        this -> sourcePort = -1;
        this -> destinationPort = -1;
    } 
     // TODO: Convertir a ints
};

void Registry::print(){
    this -> printDate();
    std::cout << "\t" << this -> hour
    << "\t" << this -> sourceIp
    << "\t" << this -> sourcePort 
    << "\t" << this -> sourceName
    << "\t" << this -> destinationIp
    << "\t" << this -> destinationPort
    << "\t" << this -> destinationName
    << std::endl << "========================" << std::endl;
}

void Registry::printDate(){
    std::cout << this -> date.tm_mday << "/" << this -> date.tm_mon+1 << "/" << this -> date.tm_year+1900;
}

#endif