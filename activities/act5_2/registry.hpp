#ifndef registry_hpp
#define registry_hpp
#include <ctime>
#include <string>

using namespace std;

class Registry {
    public:
        Registry(
            string date, 
            string hour, 
            string sourceIp,
            string sourcePort, 
            string sourceName,
            string destinationIp, 
            string destinationPort, 
            string destinationName
        );

        Registry();

        tm date; 
        string datestring;
        string hour; 
        string sourceIp; 
        int sourcePort; 
        string sourceName; 
        string destinationIp;
        int destinationPort; 
        string destinationName; 

        void print();
        void printDate();
};

Registry::Registry (
    string _date, 
    string _hour, 
    string _sourceIp,
    string _sourcePort, 
    string _sourceName,
    string _destinationIp, 
    string _destinationPort,
    string _destinationName
){
    struct tm tm;
    const char *f = _date.c_str();
    strptime(f, "%d-%m-%y", &this->date);

    this->datestring = _date;
    this->hour = _hour;
    this->sourceIp = _sourceIp;
    this->sourceName = _sourceName;
    this->destinationIp = _destinationIp;
    this->destinationName = _destinationName;

    try {
        this->sourcePort = stoi(_sourcePort, nullptr, 10);
        this->destinationPort = stoi(_destinationPort, nullptr, 10);
    } catch(...){
        this->sourcePort = -1;
        this->destinationPort = -1;
    }
};

void Registry::print(){
    this->printDate();
    cout << "\t" << this->hour
    << "\t" << this->sourceIp
    << "\t" << this->sourcePort 
    << "\t" << this->sourceName
    << "\t" << this->destinationIp
    << "\t" << this->destinationPort
    << "\t" << this->destinationName
    << endl << "========================" << endl;
}

void Registry::printDate(){
    cout << this->date.tm_mday << "/" << this->date.tm_mon+1 << "/" << this->date.tm_year+1900;
}

#endif