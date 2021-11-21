/*
 *
 * Main file
 * main.cpp
 * Emiliano Cabrera A01025453, Do Hyun Nam A01025276
 * 
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cwctype> 
#include <ctime>
#include <string>

#include "graph.hpp"
#include "reader.hpp"
#include "compConnections.hpp"

class Date{
    public:
        tm date;
        Date( tm date ){
            this->date = date;
        }

        friend bool operator == (Date d, Date dd){
            return (
                d.date.tm_mday == dd.date.tm_mday &&
                d.date.tm_mon == dd.date.tm_mon &&
                d.date.tm_year == dd.date.tm_year
            );
        }

        friend bool operator != (Date d, Date dd){
            return (
                d.date.tm_mday != dd.date.tm_mday ||
                d.date.tm_mon != dd.date.tm_mon ||
                d.date.tm_year != dd.date.tm_year
            );
        }

        friend bool operator < (Date d, Date dd){
            return (
                d.date.tm_mday < dd.date.tm_mday ||
                d.date.tm_mon < dd.date.tm_mon ||
                d.date.tm_year < dd.date.tm_year
            );
        }
        
        std::string toString(){
            return std::to_string(this->date.tm_mday) + "/" + std::to_string(this->date.tm_mon+1) + "/" + std::to_string(this->date.tm_year+1900);
        }

};

// Imprimir vectores
void print_vector(std::vector<Registry> arr){
    for (int i = 0; i < arr.size(); i++) arr[i].print();
    std::cout << std::endl;
};

// Búsqueda secuencial
int sequentialSearch(std::vector<Registry> d, bool (*condition)(Registry r) ){
    for (int i = 0; i<d.size(); i++){
        if (condition(d[i]) ) return i;
    }
    return -1;
}
// Busqueda secuencial (sobrecarga)
int sequentialSearch( std::vector<Registry> d, bool (*condition)(Registry a, Registry b), Registry r ){
    for (int i = 0; i < d.size(); i++){
        if (condition(d[i], r) ) return i;
    }
    return -1;
}


bool isAbnormal(std::string name){
    if (name.size() >= 20) return true;

    for (int i = 0; i < name.size(); i++){
        if (isalpha(name[i]) == false && name[i] != '.' && name[i] != '-'&&  name[i] != '/' ){
            return true;  
        }
    }
    return false; 
}

bool isInternal(std::string IPInput){
    std::string IPBase = "172.26.89.0";
    for (int i = 0; i < 10; i++){
        if (IPBase[i] != IPInput[i]) return false;
    }
    return true; 
}

std::string findAbnormals(std::map<std::string, CompConnections> comps){
    std::map<std::string, CompConnections>::iterator it;

    for (it = comps.begin(); it != comps.end(); it++){
        if (isAbnormal(it -> second.name)) return it -> first;
    }
    return "";
}


int compsWithInConnections(std::map<std::string, CompConnections> comps){ 
    int n = 0;
    std::map<std::string, CompConnections>::iterator it;

    for (it = comps.begin(); it != comps.end(); it++ ){
        if (it -> second.name.find("reto.com") != std::string::npos && it->second.inConnections.size() >= 1) n++;
    }
    return n;
} 

int main(int argc, const char * argv[]){
    Reader r; 
    std::vector<Registry> data = r.readFile();
    std::vector<Registry>::iterator vec_it;
    
    std::set<std::pair<std::string,std::string>> connections_set, repeater_set;
    std::set<std::pair<std::string,std::string>>::iterator set_it, set_it_2;

    Graph<std::string> connections_graph;

    for(vec_it = data.begin(); vec_it != data.end(); vec_it++){
        if(isInternal(vec_it -> sourceIp) || isInternal(vec_it -> destinationIp)) connections_set.insert(make_pair(vec_it -> sourceIp, vec_it -> destinationIp));
    }

    repeater_set = connections_set;

    bool flag;

    for(set_it = connections_set.begin(); set_it != connections_set.end(); set_it++){
        connections_graph.add_node(set_it -> first);

        flag = false;

        for(set_it_2 = repeater_set.begin(); set_it_2 != repeater_set.end(); set_it_2++){
            if(set_it -> second == set_it_2 -> first) flag = true;
        }
        
        if(!flag) connections_graph.add_node(set_it -> second);
    }

    for(set_it = connections_set.begin(); set_it != connections_set.end(); set_it++){
        connections_graph.add_edge_element(set_it -> first, set_it -> second);
    }


}