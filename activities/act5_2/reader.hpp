#ifndef reader_hpp
#define reader_hpp
#include <string>
#include "registry.hpp"
#include <fstream>
#include <vector>
#include <iostream>

class Reader{
    public: 
        Reader() = default; 
        ~Reader() = default;
        
        std::vector<Registry> readFile(){
            std::ifstream ip("equipo5.csv");
            std::vector<Registry> regs; 
            
            if (!ip.is_open()){
                std::cout << "Error: File Open" << std::endl; 
            }

            std::string date; 
            std::string hour; 
            std::string sourceIp; 
            std::string sourcePort; 
            std::string sourceName; 
            std::string destinationIp; 
            std::string destinationPort; 
            std::string destinationName;

            while(ip.good()){
                getline(ip, date, ','); 
                getline(ip, hour, ',');
                getline(ip, sourceIp, ',');
                getline(ip, sourcePort, ',');
                getline(ip, sourceName, ',');
                getline(ip, destinationIp, ',');
                getline(ip, destinationPort, ',');
                getline(ip, destinationName, '\n');
                regs.push_back(Registry(date, hour, sourceIp, sourcePort, sourceName, destinationIp, destinationPort, destinationName)); 
            }

            ip.close(); 
            
            return regs; 
    }
};

#endif