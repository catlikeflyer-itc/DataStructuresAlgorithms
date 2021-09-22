#include <iostream>
#include <vector>
#include <map>
#include "reader.hpp"

std::map <std::string, int> mails;
std::map <int, int> puertos;

// Print each vector
void print_vector(std::vector<Registry> vec){
    for (int i = 0; i < vec.size(); i++) vec[i].print();
    std::cout << std::endl;
};

// Sequential search
int sequentialSearch( std::vector<Registry> d, bool (*condition)(Registry r) ){
    for(int i = 0; i<d.size(); i++){
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

// ============================================================================
bool goesAfter(Registry a, Registry b){
    return (
        a.date_a.tm_mday > b.date_a.tm_mday &&
        a.date_a.tm_mon >= b.date_a.tm_mon &&
        a.date_a.tm_year >= b.date_a.tm_year
    );
}

bool belongsTo(Registry r){
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

bool isServerCalled(Registry r){
    return r.sourceName_a == "server.reto.com" || r.destinationName_a == "server.com";
}

bool isEmail(Registry r){
    //El puerto 993 se usa para mail
    if(r.destinationPort_a == 993){
        mails[r.destinationName_a]++; 
    }
    return false; 
}

bool isPort(Registry r){
    if(r.destinationPort_a < 1000 && r.destinationPort_a > 0){
        // Añadir al diccionario
        puertos[r.destinationPort_a]++;
    }
    return false; 
}

std::string getBaseIp(std::vector<Registry> d){
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
        << "El archivo tiene " << data.size() << " registros\n" << std::endl;
    
    //2.¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?
    std::cout << "2. ¿Cuántos récords hay del segundo día registrado? ¿Qué día es?" << std::endl;
    int firstDay = sequentialSearch(data, *goesAfter, data[0]);
    int secondDay = sequentialSearch(data, *goesAfter, data[firstDay]) - firstDay;
    
    /*
    cout<<"En el primer día (";
    datos[0].printDate();
    cout<<") hubieron "<<primerDiaCount<<" datos"<<endl;
    cout<<"En el segundo día (";
    datos[segundoDiaCount].printDate();
    cout<<") hubieron "<<segundoDiaCount<<" datos"<<endl<<endl;

    //3. ¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?
    cout<<"3\t¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?"<<endl;
    int perteneceCount = busquedaSecuencial(datos, *perteneceA);
    cout<<( perteneceCount==0 ? "No." : "Sí." )<<endl;

    //4. ¿Cuál es la dirección de la red interna de la compañía?
    // Sustituir para usar comparadores y búsqueda secuencial. DONE
    cout<<"4\t¿Cuál es la dirección de la red interna de la compañía?"<<endl;
    cout<<"La dirección de la red interna es: "<<obtenerIPBase(datos)<<endl;
    
    //5. ¿Alguna computadora se llama server.reto.com?
    cout<<"5\t¿Alguna computadora se llama server.reto.com?"<<endl;
    int serverCount = busquedaSecuencial(datos, *seLlamaServer);
    cout<<( serverCount<0 ? "No." : "Sí." )<<endl;

    //6. ¿Qué servicio de mail utilizan? 
    cout<<"6\t¿Qué servicio de mail utilizan?"<<endl;
    int mailCount = busquedaSecuencial(datos, *esCorreo);
    std::cout << "Mail" << "\t\t" << "Cantidad"<< "\n";
    for (const auto& x : mails ) {
        std::cout << x.first << " \t" << x.second << "\n";
    }

    //7. Considerando solamento los puertos destino: 
    //¿Qué puertos abajo del 1000 se están usando? Lista los puertos. 
    cout<<"7\t¿Qué puertos abajo del 1000 se están usando?"<<endl;
    int puertosCount = busquedaSecuencial(datos, *esPuerto);
    std::cout << "Puerto" << " \t" << "Cantidad"<< "\n";
    for (const auto& x : puertos ) {
        std::cout << x.first << " \t" << x.second << "\n";
    }
    */
   
    return 0;
}