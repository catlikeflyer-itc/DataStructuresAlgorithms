/*
 *
 * Main file
 * main.cpp
 * Emiliano Cabrera A01025453, Do Hyun Nam A01025276
 * 
 */

#include "reader.hpp"
#include "compConnections.hpp"
#include "hash.cpp"

#include <vector>
#include <set>
#include <iostream>

#pragma once

bool isAbnormal(std::string name){
    if (name.size() >= 20) return true;

    for (int i = 0; i < name.size(); i++){
        if (isalpha(name[i]) == false && name[i] != '.' && name[i] != '-'&&  name[i] != '/' ){
            return true;  
        }
    }
    return false; 
}

int main(int argc, const char * argv[]){
    Reader r; 
    std::vector<Registry> data = r.readFile();
    std::vector<Registry>::iterator v_it;

    std::set<std::string> not_reto, ip_set;
    std::set<std::string>::iterator s_it;

    for(v_it = data.begin(); v_it != data.end(); v_it++){
        std::size_t source_find = v_it->sourceName.find("reto.com");
        std::size_t destination_find = v_it->destinationName.find("reto.com");

        if(source_find == std::string::npos) not_reto.insert(v_it->sourceName);
        if(destination_find == std::string::npos) not_reto.insert(v_it->destinationName);

        ip_set.insert(v_it->destinationIp);
        ip_set.insert(v_it->sourceIp);
    }

    std::set<std::pair<std::string, CompConnections *>> ip_dictionary;

    for(s_it = ip_set.begin(); s_it != ip_set.end(); s_it++){
        CompConnections * c = new CompConnections();

        c->IP = *s_it;
        c->fill(data);

        ip_dictionary.insert(std::make_pair(*s_it,c));
    }


    // 1.-
    std::set<std::string> weird_set;

    for(v_it = data.begin(); v_it != data.end(); v_it++){
        if(isAbnormal(v_it->destinationName)) weird_set.insert(v_it->destinationName);
        if(isAbnormal(v_it->sourceName)) weird_set.insert(v_it->sourceName);
    }

    std::cout << "Abnormales: ";

    for(s_it = weird_set.begin(); s_it != weird_set.end(); s_it++){
        std::cout << std::endl << "\t" << *s_it;
    }

    std::cout << std::endl;

    // 2.-
    
    
}