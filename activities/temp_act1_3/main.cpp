#include <iostream>
#include <vector>
#include <map>
#include "reader.hpp"

std::map <std::string, int> mails; // Stores mail domain count
std::map <int, int> ports; // Stores each port's count

// Print each vector
void print_vector(std::vector<Registry> vec){
    for (int i = 0; i < vec.size(); i++) vec[i].print();
    std::cout << std::endl;
};

// Sequential search
int sequentialSearch( std::vector<Registry> d, bool (*condition)(Registry r) ){
    for(int i = 0; i < d.size(); i++){
        if( condition(d[i]) ) return i;
    }
    return -1;
}
// Sequential search overloading
int sequentialSearch( std::vector<Registry> d, bool (*condition)(Registry a, Registry b), Registry r ){
    for(int i = 0; i<d.size(); i++){
        if( condition(d[i], r) ) return i;
    }
    return -1;
}

// Binary search
int binarySearch(std::vector<Registry>d, bool (*condition)(Registry r), int start, int end){    
    int med = start + (end - start)/2;

    if (end <= start) return -1;
    if (condition(d[med])) return med;

    int left = binarySearch(d, *condition, start, med-1);
    if (left != -1) return left; 

    int right = binarySearch(d, *condition, med+1, end);
    if (right != -1) return right;

    return -1;
}


bool goesAfter(Registry a, Registry b){
    // Compares two different registry dates 

    return (
        a.date_a.tm_mday > b.date_a.tm_mday &&
        a.date_a.tm_mon >= b.date_a.tm_mon &&
        a.date_a.tm_year >= b.date_a.tm_year
    );
}

bool belongsTo(Registry r){
    // Checks if it belongs to Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel, Raymond

    return(
        r.sourceName_a == "jeffrey.reto.com" ||
        r.sourceName_a == "betty.reto.com" ||
        r.sourceName_a == "katherine.reto.com" ||
        r.sourceName_a == "scott.reto.com" ||
        r.sourceName_a == "benjamin.reto.com" ||
        r.sourceName_a == "samuel.reto.com" ||
        r.sourceName_a == "raymond.reto.com"
    );
}

std::vector<bool> checkNames(Registry r, std::vector<bool> name_flags){     
    if(name_flags[0] == true && r.sourceName_a == "jeffrey.reto.com"){
        std::cout << "Jeffrey" << std::endl;
        name_flags[0] = false;
    }
    else if(name_flags[1] == true && r.sourceName_a == "betty.reto.com"){
        std::cout << "Betty" << std::endl;
        name_flags[1] = false;
    }
    else if(name_flags[2] == true && r.sourceName_a == "katherine.reto.com"){
        std::cout << "Katherine" << std::endl;
        name_flags[2] = false;
    }
    else if(name_flags[3] == true && r.sourceName_a == "scott.reto.com"){
        std::cout << "Scott" << std::endl;
        name_flags[3] = false;
    }
    else if(name_flags[4] == true && r.sourceName_a == "benjamin.reto.com"){
        std::cout << "Benjamin" << std::endl;
        name_flags[4] = false;
    }
    else if(name_flags[5] == true && r.sourceName_a == "samuel.reto.com"){
        std::cout << "Samuel" << std::endl;
        name_flags[5] = false;
    }
    else if(name_flags[6] == true && r.sourceName_a == "raymond.reto.com"){
        std::cout << "Raymond" << std::endl;
        name_flags[6] = false;
    }

    return name_flags;
}

bool isServerCalled(Registry r){
    // Checks server name

    return r.sourceName_a == "server.reto.com" || r.destinationName_a == "server.com";
}

bool isEmail(Registry r){
    // Check if it is port 993, used for emails

    if(r.destinationPort_a == 993){
        mails[r.destinationName_a]++;  // Adds mail to mail counter dictionary (map)
    }
    return false; 
}

bool isPort(Registry r){
    // Checks if port is valid between 1  to 999

    if(r.destinationPort_a < 1000 && r.destinationPort_a > 0){
        ports[r.destinationPort_a]++; // Adds to ports dictionary (map)
    }
    return false; 
}

std::string getBaseIp(std::vector<Registry> d){
    // Returns the base IP after parsing source

    int i = sequentialSearch(d, [](Registry r){ return r.sourceIp_a != "-";});
    std::string ip = d[i+1].sourceIp_a;

    for(int i = 0; i<3; i++) ip.pop_back();
    ip.append(".0"); 

    return ip;
}

int main(void){
    Reader r; 
    std::vector<Registry> data = r.readFile(); 

    //1. ¿Cuántos registros tiene tu archivo?
    std::cout << "1. ¿Cuántos registros tiene tu archivo?" << std::endl
        << data.size() << std::endl;
    
    //2.¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?
    std::cout << "2. ¿Cuántos récords hay del segundo día registrado? ¿Qué día es?" << std::endl;
    int firstDay = sequentialSearch(data, *goesAfter, data[0]);
    int secondDay = sequentialSearch(data, *goesAfter, data[firstDay]) - firstDay;
    
    std::cout << "Datos en el primer día (";
    data[firstDay].printDate();
    std::cout << "): " << firstDay << std::endl;

    std::cout << "Datos en el segundo día (";
    data[secondDay].printDate();
    std::cout << "): " << secondDay << std::endl;

    //3. ¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?
    std::cout << "3. ¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?" << std::endl;
    int belongs = sequentialSearch(data, *belongsTo);
    std::cout << (belongs > 0 ? "No" : "Si" ) << std::endl;

    std::vector<bool> name_flags = {true,true,true,true,true,true,true};
    for(int i = 0; i<data.size() - 1; i++){
        name_flags = checkNames(data[i] ,name_flags);
    }

    //4. ¿Cuál es la dirección de la red interna de la compañía?
    std::cout << "4. ¿Cuál es la dirección de la red interna de la compañía?" << std::endl;
    std::cout << getBaseIp(data) << std::endl;
    
    //5. ¿Alguna computadora se llama server.reto.com?
    std::cout << "5. ¿Alguna computadora se llama server.reto.com?" << std::endl;
    int serverCount = sequentialSearch(data, *isServerCalled);
    std::cout << (serverCount < 0 ? "No" : "Si" ) << std::endl;

    //6. ¿Qué servicio de mail utilizan? 
    std::cout << "6. ¿Qué servicio de mail utilizan?" << std::endl;
    int mailCount = sequentialSearch(data, *isEmail);
    std::cout << "Mail" << "\t\t" << "Cantidad"<< "\n";
    for (const auto& x : mails ) {
        std::cout << x.first << " \t" << x.second << "\n";
    }

    //¿Qué puertos abajo del 1000 se están usando? Lista los puertos. 
    std::cout << "7. ¿Qué puertos abajo del 1000 se están usando?" << std::endl;
    int puertosCount = sequentialSearch(data, *isPort);

    std::cout << "Puerto" << " \t" << "Cantidad"<< "\n";
    for (const auto& x : ports ) {
        std::cout << x.first << " \t" << x.second << "\n";
    }
   
    return 0;
}