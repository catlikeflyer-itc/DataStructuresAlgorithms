#ifndef registry_h 
#define registry_h
#include <time.h>
#include <ctime>
#include <string>
#include <iostream>

class Registry {
    public:
        // Constructor with params from the csv file
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

        // Default constructor
        Registry(); 
        
        // Attributes of class registry, differentiated from constructor params using an "_a"
        tm date_a;
        std::string dateString_a;
        std::string hour_a; 
        std::string sourceIp_a; 
        int sourcePort_a; 
        std::string sourceName_a; 
        std::string destinationIp_a; 
        int destinationPort_a; 
        std::string destinationName_a;

        // Method declaration of the class 
        void print();
        void printDate();
};

// Constructor overloading to set the class attributes from the params taken when constructed
Registry::Registry(

    // Private scope params just for Registry
    std::string _date, 
    std::string _hour, 
    std::string _sourceIp,
    std::string _sourcePort, 
    std::string _sourceName,
    std::string _destinationIp, 
    std::string _destinationPort,
    std::string _destinationName
){
    struct tm tm; // Time structure that stores time broken into components

    const char *f = _date.c_str();
    strptime(f, "%d-%m-%y", &this -> date_a); // Only works with Unix systems

    this -> dateString_a = _date;
    this -> hour_a = _hour;
    this -> sourceIp_a = _sourceIp;
    this -> destinationIp_a = _destinationIp;
    this -> sourceName_a = _sourceName;
    this -> destinationName_a = _destinationName;

    try {
        this -> sourcePort_a = stoi(_sourcePort, nullptr, 10);
        this -> destinationPort_a = stoi(_destinationPort, nullptr, 10);
    } 
    catch(...) {
        this -> sourcePort_a = -1;
        this -> destinationPort_a = -1;
    }
};
void Registry::print(){
    this -> printDate();
    std::cout << "\t" << this -> hour_a
    << "\t" << this -> sourceIp_a
    << "\t" << this -> sourcePort_a 
    << "\t" << this -> sourceName_a
    << "\t" << this -> destinationIp_a
    << "\t" << this -> destinationPort_a
    << "\t" << this -> destinationName_a
    <<std::endl<<"========================"<<std::endl;
}

void Registry::printDate(){
    std::cout << this -> date_a.tm_mday << "/" << this -> date_a.tm_mon+1 << "/" << this -> date_a.tm_year+1900;
}

#endif
