#include <iostream>
#include <vector>
#include <map>
#include "reader.hpp"
#include "compConnections.hpp"
#include <set>
#include <cwctype> 
#include <ctime>
#include <string>

using namespace std;

// Imprimir vectores
void print_vector(vector<Registry> arr){
    for (int i = 0; i < arr.size(); i++) arr[i].print();
    cout << endl;
};

void agregarNoRetoASet(set<string> s, vector<Registry> datos){
    for(int i=0; i<5000; i++){
        if(datos[i].sourceName.find(".reto.com") || datos[i].sourceName.find("-") ){
            s.insert(datos[i].sourceName); 
        }
    }
}

void llenarComputadoras(map<string, CompConnections> &computadoras, vector<Registry> datos){
    // throwback a nuestro debugging de una hora, porque no estábamos editando el map original :)
    for(int i=0; i<6000; i++){ //Cambiar a datos.size()
        CompConnections c(datos[i].sourceIp, datos[i].sourceName);
        c.fill(datos);
        computadoras.insert(pair<string, CompConnections>(datos[i].sourceIp,c));
    }
}

void agregarNoRetoASetyLlenarComputadoras(set<string> s, map<string, CompConnections> &computadoras, vector<Registry> datos){
    for(size_t i=0; i<datos.size(); i++){
        if(datos[i].sourceName.find(".reto.com") || datos[i].sourceName.find("-") ){
            s.insert(datos[i].sourceName); 
        }
        // Correr si la IP origen no está en el map
        if( datos[i].sourceIp != "-" && computadoras.find(datos[i].sourceIp) == computadoras.end() ){
            CompConnections c(datos[i].sourceIp, datos[i].sourceName);
            c.fill(datos);
            computadoras.insert(pair<string, CompConnections>(datos[i].sourceIp,c));
        }
        // Correr si la IP destino no está en el map
        if( datos[i].destinationIp != "-" && computadoras.find(datos[i].destinationIp) == computadoras.end()){
            CompConnections c(datos[i].destinationIp, datos[i].destinationName);
            c.fill(datos);
            computadoras.insert(pair<string, CompConnections>(datos[i].destinationIp,c));
        }
    }
}

bool esAnomalo(string nombre){
    // largo
    // caracteres alfanumericos
    if (nombre.size() >= 20) return true;
    for(int i=0; i<nombre.size(); i++){
        if(isalpha(nombre[i]) == false && nombre[i] != '.' && nombre[i] != '-'&&  nombre[i] != '/' ){
            return true;  
        }
    }
    return false; 
}

bool esInterna(string IPInput){
    string IPBase = "192.169.29.0";
    for(int i=0; i<10; i++){
        if( IPBase[i] != IPInput[i] ) return false;
    }
    return true; 
}

string encontrarAnomalos(map<string, CompConnections> computadoras){
    map<string, CompConnections>::iterator it;
    for (it = computadoras.begin(); it != computadoras.end(); it++){
        if (esAnomalo( it->second.name )) return it->first;
    }
    return "";
}


int computadorasConConexionesEntrantes(map<string, CompConnections> computadoras){ 
    int n = 0;
    map<string, CompConnections>::iterator it;
    for(it = computadoras.begin(); it != computadoras.end(); it++ ){
        if(it->second.name.find("reto.com") != string::npos && it->second.inConnections.size() >= 1) n++;
    }
    return n;
} 

set<string> obtenerIPsEntrantes(map<string, CompConnections> computadoras) {
    set<string> ipsUnicas;
    map<string, CompConnections>::iterator it;
    int n = 0;

    for(it = computadoras.begin(); it != computadoras.end(); it++ ){
        if (it->second.name.find(".reto.com") == string::npos /*no lo encontró*/ ){
            n++;
            // Convertir a vector para poder acceder los índices de manera más fácil ;D
            std::vector<Connection> conexionesV;
            conexionesV.reserve(it->second.inConnections.size());
            std::copy(std::begin(it->second.inConnections), std::end(it->second.inConnections), std::back_inserter(conexionesV));
            
            set<string> nombresPorComputadoraUnicos;


            for (int i = 0; i < conexionesV.size(); i++ ){
                if (conexionesV[i].port != 67 ){
                    nombresPorComputadoraUnicos.insert(conexionesV[i].host);
                    ipsUnicas.insert( conexionesV[i].IP );
                }
            }
        }
    }

   return ipsUnicas; 
}

int main(void){
    Reader r; 
    vector<Registry> datos = r.readFile(); 
    set<string> notReto; 
    map<string, CompConnections> computadoras; 

    agregarNoRetoASetyLlenarComputadoras(notReto, computadoras, datos);

    cout << "Hay " << computadoras.size() << " computadoras" << endl;

    cout << endl;

    cout << "1. ¿Hay algún nombre de dominio que sea anómalo?" << endl; //ds19smmrn47jp3osf6x4.com
    cout << "\t" << (encontrarAnomalos(computadoras) != "" ? "Sí." : "No.") << endl; 
    
    cout << endl;

    // De los nombres de dominio encontrados en el paso anterior, ¿Cuál es su ip? 
    // ¿Cómo determinarías esta información de la manera más eficiente en complejidad temporal?
    cout << "2. ¿Cuál es su IP? ¿Cómo determinarías esta información de la manera más eficiente en complejidad temporal?" << endl;
    string ipAnomala = encontrarAnomalos(computadoras); 
    cout << "\tLa IP es " << ipAnomala << endl;  
    cout << "\tCon una inspección visual identificamos: http://36ytsfs8ph6iczxio1i4.net" << endl; 
    cout << "\tHicimos una función prototipo de cómo se podrían encontrar dominios anómalos: encontrarAnomalos(datos)." << endl; 
    cout << "\tPara esto usamos como parámetros el largo del dominio y si contiene caracteres no alfanuméricos, " << endl; 
    cout << "\tya que los dominios largos con una extraña combinación de carácteres alfanuméricos son las características " << endl; 
    cout << "\tmás comúnes de los dominios anómalos. " << endl; 
    cout << "\tSi se entrenara un modelo de ML para que pudiese reconocer a los dominios anómalos podríamos identificarlos" << endl;    cout << "\tSi se entrenara un modelo de ML para que pudiese reconocer a los dominios anómalos podríamos identificarlos" << endl;
    cout << "\tal momento de que entren o salgan, en una complejidad de O(1)." << endl;

    cout << endl;

    //De las computadoras pertenecientes al dominio reto.com determina la cantidad de ips que tienen al menos una conexión entrante. 
    //(Recuerda que ya tienes la dirección de la red y el último octeto puede tener computadoras del .1 al .254). 
    //Imprime la cantidad de computadoras.
    cout << "3. De las computadoras pertenecientes al dominio reto.com determina la cantidad de ips que tienen al menos una conexión entrante." << endl; 
    cout << "\t" << computadorasConConexionesEntrantes(computadoras) << " computadoras de la red interna con al menos una conexion entrante" << endl;

    cout << endl;

    //Toma algunas computadoras que no sean server.reto.com o el servidor dhcp. Pueden ser entre 5 y 150. Obtén las ip únicas de las conexiones entrantes.
    cout << "4. Toma algunas computadoras que no sean server.reto.com o el servidor dhcp. Pueden ser entre 5 y 150. Obtén las ip únicas de las conexiones entrantes." << endl;
    set<string> conexiones = obtenerIPsEntrantes(computadoras);
    
    for (auto it = conexiones.begin(); it != conexiones.end(); ++it){
        cout << '\t' << *it << endl;
    }

    cout << endl;

    cout << "5. Considerando el resultado de las preguntas 3 y 4, ¿Qué crees que esté ocurriendo en esta red? (Pregunta sin código)" << endl;
    cout << "\t32 computadoras internas tienen conexiones entrantes. Esto significa que computadoras externas están intentando acceder a " << endl;
    cout << "\tla información. De las conexiones entrantes, puede identificarse que existe solo una conexión al dominio anómalo." << endl;

    cout << endl;

    cout << "6. Para las ips encontradas en el paso anterior, determina si se han comunicado con los datos encontrados en la pregunta 1." << endl;
    // Iterar conexiones entrantes de ip anomala;
    // Ver si alguna conexión pertnece a conexiones
    list<Connection> conexionesEntrantesAIPAnomala = computadoras[ipAnomala].inConnections;
    map<string, int> culpable;

    for (auto it = conexionesEntrantesAIPAnomala.begin(); it != conexionesEntrantesAIPAnomala.end(); ++it){
        culpable[ it->host ] ++;
    }
    for (auto it = culpable.begin(); it != culpable.end(); it++){
        cout << "\t" << it->first << ": " << it->second << endl;
    }

    cout << endl;

    cout << "7. En caso de que hayas encontrado que las computadoras del paso 1 y 4 se comunican, determina en qué fecha ocurre la primera comunicación entre estas 2 y qué protocolo se usó."<<endl;
    cout << "\tLa computadora de Amanda se infectó el: "; 
    conexionesEntrantesAIPAnomala.back().imprimirFecha();
    cout << endl; 
    cout << "\tPuerto: " << conexionesEntrantesAIPAnomala.back().port << endl;
    cout << endl;

    return 0;
}