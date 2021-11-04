/*
 *
 * Main file
 * main.cpp
 * Emiliano Cabrera A01025453, Do Hyun Nam A01025276
 * 
 */
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>

#include "bst.hpp"
#include "compConections.hpp"
#include "connection.hpp"
#include "reader.hpp"

std::map<std::string,int> conexionesPorDia(std::string f, std::vector<Registry> d){
    std::string reto = "reto.com";
    std::string dash = "-";

    std::vector<std::string> domain;

    std::map<std::string, int> connect;

    for(int i = 0; i < d.size(); i++){
        if(d[i].destinationName_a != dash && d[i].destinationName_a.find(reto) == std::string::npos){
        domain.push_back(d[i].destinationName_a);
        }
    }

    sort(domain.begin(),domain.end());
    domain.erase(unique(domain.begin(), domain.end()),domain.end());

    int counter;

    for(auto dom : domain){
        counter = 0;

        for(int i = 0; i < d.size(); i++){
            if(dom == d[i].destinationName_a && d[i].dateString_a == f){
                counter++;
            }
        }
        
        connect.insert(std::pair<std::string,int>(dom,counter));
    }    

    return connect;
}

void top(int n, std::string f, std::vector<Registry> d){
    std::map<std::string,int> connect = conexionesPorDia(f, d);

    BinarySearchTree * bst = new BinarySearchTree();

    for(auto con : connect){
        bst->insertNode(con.first,con.second);
    }

    std::cout << "Fecha: " << f << "\tElementos: " << n << std::endl;
    bst->printInOrder();
}

int main(int argc, const char* argv[]){
    Reader r; 
    std::vector<Registry> data = r.readFile();
    std::vector<std::string> dates;
    
    for(int i = 0; i < data.size(); i++){
        dates.push_back(data[i].dateString_a);
    }

    sort(dates.begin(),dates.end());
    dates.erase(unique(dates.begin(), dates.end()),dates.end());

    for(int i = 0; i < dates.size(); i++){
        std::cout << std::endl;
        top(5, dates[i], data);
    }
}