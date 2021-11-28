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

#include "compConections.hpp"
#include "connection.hpp"
#include "reader.hpp"

int main(int argc, const char * argv[]){
    if(argc != 2){
        std::cout << "Numero incorrecto de argumentos. Por favor use de la siguiente manera:" << std::endl << "<nombre_ejecutable> <int>" << std::endl;
        exit(1);
    }

    Reader r; 
    std::vector<Registry> data = r.readFile(); 

    std::string ip_base = "192.168.29.", ip = ip_base + std::string(argv[1]);
    std::string name;
    std::string last_ip;

    for(int i = 0; i < data.size() - 1; i++){
        if(data[i].sourceIp_a == ip){
            name = data[i].sourceName_a;
            break;
        }
    }

    CompConnections connect(ip,name);


    for(int i = 0; i < data.size() - 1; i++){
        if(data[i].sourceIp_a == ip){
            connect.addToOutgoingConnections(data[i].destinationIp_a,data[i].destinationPort_a,data[i].destinationName_a);
        }
        else if(data[i].destinationIp_a == ip){
            connect.addToIncomingConnections(data[i].sourceIp_a,data[i].sourcePort_a,data[i].sourceName_a);
            last_ip = data[i].sourceIp_a;
        }
    }

    // ---
    std::cout << "1.- Que direccion ip estas usando?" << std::endl;
    std::cout << "IP: " << ip << std::endl;
    // ---

    // ---
    std::cout << "2.- Cual fue la direccion IP de la ultima conexion que recibio esta computadora? Es interna o externa?" << std::endl;
    std::cout << "IP: " << last_ip;

    if(last_ip.find(ip_base) != std::string::npos){
        std::cout << "\tInterna" << std::endl;
    }
    else{
        std::cout << "\tExterna" << std::endl;
    }
    
    // ---
    
    Connection aux_c;
    int counter;

    // ---
    std::cout << "3.- Cuantas conexiones entrantes tiene esta computadora?" << std::endl;    
    
    std::queue<Connection> in_aux_q;
    counter = 0;
   
    while(!connect.inConnections.empty()){
        aux_c = connect.inConnections.top();
        connect.inConnections.pop();
        counter++;
        in_aux_q.push(aux_c);
    }

    std::cout << "Conexiones entrantes: " << counter << std::endl;
    
    while(!in_aux_q.empty()){
        connect.addToIncomingConnections(in_aux_q.front().ip, in_aux_q.front().port, in_aux_q.front().host);
        in_aux_q.pop();
    }
    // ---

    std::vector<Connection> out_connections;

    // ---
    std::cout << "4.- Cuantas conexiones salientes tiene esta computadora?" << std::endl;
    
    std::stack<Connection> out_aux_s;
    counter = 0;
    
    while(!connect.outConnections.empty()){
        aux_c = connect.outConnections.front();
        connect.outConnections.pop();
        counter++;
        out_aux_s.push(aux_c);
        out_connections.push_back(aux_c);
    }

    std::cout << "Conexiones salientes: " << counter << std::endl;
    
    while(!out_aux_s.empty()){
        connect.addToOutgoingConnections(out_aux_s.top().ip, out_aux_s.top().port, out_aux_s.top().host);
        out_aux_s.pop();
    }
    // ---

    // ---    
    std::cout << "5.- Tiene esta computadora 3 conexiones seguidas a un mismo sitio web?" << std::endl;

    bool r_flag; // true = si hay 3 repetidas, false = no hay 3 repetidas
    std::string r_ip;

    for(int i = 0; i < out_connections.size() - 3; i++){
        if(out_connections[i].ip == out_connections[i + 1].ip && out_connections[i + 1].ip == out_connections[i + 2].ip){
            r_flag = true;
            r_ip = out_connections[i].ip;
            break;
        }
        else{
            r_flag = false;
        }
    }

    if(r_flag == true){
            std::cout << "Si hay una conexion seguida a " << r_ip << std::endl;
        }
        else if(r_flag == false){
            std::cout << "No hay una conexion repetida" << std::endl;
        }
    // ---

    return 0;
}