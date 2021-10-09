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

    std::string ip = "192.168.29." + std::string(argv[1]);
    std::string name;
    bool io_flag = true; // true = outgoing, false = incoming
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
            last_ip = data[i].destinationIp_a;
            io_flag = true;
        }
        else if(data[i].destinationIp_a == ip){
            connect.addToIncomingConnections(data[i].sourceIp_a,data[i].sourcePort_a,data[i].sourceName_a);
            last_ip = data[i].sourceIp_a;
            io_flag = false;
        }
    }

    // ---
    std::cout << "1.- Que direccion ip estas usando?" << std::endl;
    std::cout << "IP: " << ip << std::endl;
    // ---

    // ---
    std::cout << "2.- Cual fue la direccion IP de la ultima conexion que recibio esta computadora? Es interna o externa?" << std::endl;
    std::cout << "IP: " << last_ip;
    if(io_flag == true){
        std::cout << "\tSaliente" << std::endl;
    }
    else if(io_flag == false){
        std::cout << "\tEntrante" << std::endl;
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

    // ---
    std::cout << "4.- Cuantas conexiones salientes tiene esta computadora?" << std::endl;
    
    std::stack<Connection> out_aux_s;
    counter = 0;
    
    while(!connect.outConnections.empty()){
        aux_c = connect.outConnections.front();
        connect.outConnections.pop();
        counter++;
        out_aux_s.push(aux_c);
    }

    std::cout << "Conexiones salientes: " << counter << std::endl;
    
    while(!out_aux_s.empty()){
        connect.addToOutgoingConnections(out_aux_s.top().ip, out_aux_s.top().port, out_aux_s.top().host);
        out_aux_s.pop();
    }
    // ---

    // ---    
    std::cout << "5.- Tiene esta computadora 3 conexiones seguidas a un mismo sitio web?" << std::endl;
    /*
        <code>
    */

    // ---

    return 0;
}