#ifndef reader_h 
#define reader_h
#include <string>
#include "registry.hpp"
#include <fstream>
#include <vector>

class Reader {
    public: 
        // Default constructor
        Reader() = default; 

        // Reads the csv file and returns a vector
        std::vector<Registry> readFile(){
            std::ifstream data("equipo5.csv");
            std::vector<Registry> registries; 
            
            // Check if csv file is  in use
            if(!data.is_open()) {
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
            
            // When no problems or conflicts are detectedm it gets each row separated by a comma
            while(data.good()){
                std::getline(data, date, ','); 
                std::getline(data, hour, ',');
                std::getline(data, sourceIp, ',');
                std::getline(data, sourcePort, ',');
                std::getline(data, sourceName, ',');
                std::getline(data, destinationIp, ',');
                std::getline(data, destinationPort, ',');
                std::getline(data, destinationName, '\n');

                // Push Registry instance to vector
                registries.push_back(Registry(date, hour, sourceIp, sourcePort, sourceName, destinationIp, destinationPort, destinationName)); 
            }

            data.close(); 

            return registries; 
        }
};

#endif