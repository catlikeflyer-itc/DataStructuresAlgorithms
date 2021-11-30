#include <iostream>
#include <vector>
#include <map>
#include "reader.hpp"
#include "compConnections.hpp"
#include <set>
#include <cwctype> 
#include <ctime>
#include <string>
#include "bst.h"
using namespace std;

class Date{
    public:
        tm date;
        Date(tm date){
            this -> date = date;
        }

        /*
        Revisar y verificar formartos de la fecha
        */
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
        

        string toString(){
            return to_string(this -> date.tm_mday) + "/" + to_string(this -> date.tm_mon+1) + "/" + to_string(this -> date.tm_year+1990);
        }

};

/*
Imprimir vectores
O(n)

Return void
*/
void print_vector(vector<Registry> arr){
    for (int i = 0; i < arr.size(); i++) arr[i].print();
    cout << endl;
};

/*
Busqueda secuencial
O(n)

Returns flag
*/
int sequentialSearch(vector<Registry> d, bool (*condition)(Registry r)){
    for (int i = 0; i < d.size(); i++){
        if (condition(d[i])) return i;
    }

    return -1;
}

// Busqueda secuencial (overload)
int sequentialSearch(vector<Registry> d, bool (*condition)(Registry a, Registry b), Registry r ){
    for (int i = 0; i < d.size(); i++){
        if (condition(d[i], r)) return i;
    }

    return -1;
}

/*
Insertar las fuentes que no corresponden a "reto" a set
O(n)

Return void
*/
void addNoRetoToSet(set<string> s, vector<Registry> data){
    for (int i = 0; i < 5000; i++){
        if (data[i].sourceName.find(".reto.com") || data[i].sourceName.find("-") ){
            s.insert(data[i].sourceName); 
        }
    }
}

/*
Llenar datos de coputadoras conectadas
O(n)

Return void
*/
void fillComputers(map<string, CompConnections> &comps, vector<Registry> data){
    // throwback a nuestro debugging de una hora, porque no estábamos editando el map original :)
    for (int i = 0; i < 6000; i++){ //Cambiar a datos.size()
        CompConnections c(data[i].sourceIp, data[i].sourceName);
        c.fill(data);
        comps.insert(pair<string,CompConnections>(data[i].sourceIp,c));
    }
}

/*
Utilizando las dos funciones posteriores, ejecutarlas una tras otra 
O(2n)

Return void
*/
void addNoRetoToSetFillComputers(set<string> s, map<string, CompConnections> &comps, vector<Registry> data){
    for (size_t i = 0; i < data.size(); i++){
        if (data[i].sourceName.find(".reto.com") || data[i].sourceName.find("-") ){
            s.insert(data[i].sourceName); 
        }

        // Correr si la IP origen no está en el map
        if( data[i].sourceIp != "-" && comps.find(data[i].sourceIp) == comps.end() ){
            CompConnections c(data[i].sourceIp, data[i].sourceName);
            c.fill(data);
            comps.insert(pair<string, CompConnections>(data[i].sourceIp, c));
        }

        // Correr si la IP destino no está en el map
        if (data[i].destinationIp != "-" && comps.find(data[i].destinationIp) == comps.end()){
            CompConnections c(data[i].destinationIp, data[i].destinationName);
            c.fill(data);
            comps.insert(pair<string, CompConnections> (data[i].destinationIp, c));
        }
    }
}

bool isAbnormal(string name){
    // largo
    // caracteres alfanumericos
    if (name.size() >= 20) return true;

    for (int i = 0; i < name.size(); i++){
        if (isalpha(name[i]) == false && name[i] != '.' && name[i] != '-'&&  name[i] != '/' ){
            return true;  
        }
    }

    return false; 
}

/*
Buscar conexiones anomalas
O(n)

Return first anomaly or empty string if not found
*/
string findAbnormalities(map<string, CompConnections> comps){
    map<string, CompConnections>::iterator it;

    for (it = comps.begin(); it != comps.end(); it++){
        if (isAbnormal(it -> second.name)) return it -> first;
    }

    return "";
}

/*
Revisar cantidad de computadoras con conexiones entrantes
O(n)

Return int with quantity
*/
int compsWithInConnections(map<string, CompConnections> comps){ 
    int n = 0;
    map<string, CompConnections>::iterator it;
    for (it = comps.begin(); it != comps.end(); it++ ){
        if (it -> second.name.find("reto.com") != string::npos && it -> second.inConnections.size() >= 1) n++;
    }

    return n;
} 

/*
Revisar las IPs entrantes en las conexiones
O(n^2)

Return set of strings with IPs (no repetition)
*/
set<string> getInIps(map<string, CompConnections> comps) {
    set<string> uniqueIps;

    map<string, CompConnections>::iterator it;
    int n = 0;

    for (it = comps.begin(); it != comps.end(); it++ ){
        if (it -> second.name.find(".reto.com") == string::npos /*no lo encontró*/ ){
            n++;
            // Convertir a vector para poder acceder los índices de manera más fácil ;D
            vector<Connection> connV{begin(it->second.inConnections), end(it->second.outConnections)};
            set<string> uniqueCompNames;

            for(int i=0; i< connV.size(); i++ ){
                if ( connV[i].port != 67 ){
                    uniqueCompNames.insert(connV[i].host);
                    uniqueIps.insert( connV[i].IP );
                }
            }
        }
    }

   return uniqueIps; 
}

/*
conexionesPorDia
Recibe una fecha 
Regresa un map<string, int>
Conteniendo la cantidad de numeroDeOcurrencias entrantes a cada sitio/página que no sea "-" 
y que no pertenezca al dominio "reto.com" del día especificado por la fecha de entrada. 
*/
map<string, int> connectionsPerDay(tm date, vector<Registry> data){
    map<string, int> occurances; 

    for (int i = 0; i < data.size(); i++){
        if (data[i].date.tm_mday == date.tm_mday && data[i].date.tm_mon == date.tm_mon && data[i].date.tm_year == date.tm_year){ 
            if (data[i].destinationName.find(".reto.com") == string::npos && data[i].destinationName.find("-")== string::npos){
                occurances[data[i].destinationName]++; 
            }
        }
    }

    return occurances; 
}

// Imprime un mapa
void printMap(map<string, int> occ){
    map<string, int>::iterator it;

    for (it = occ.begin(); it != occ.end(); it++ ){
        cout << it -> first << ":\t" << it -> second << endl;
    }
}

/*
Contenga una función llamada top, la cual recibe un parámetro n de tipo int 
y una fecha. Esta función debe imprimir los n sitios con más accesos en esa fecha. 
Para ello, puedes usar la función conexionesPorDia y debes agregar los sitios a un 
BST utilizando como parámetro de ordenamiento la cantidad de numeroDeOcurrencias entrantes.
*/
void top(
    BinarySearchTree &tree, int n, tm date, map<string, int> &numeroDeOcurrencias, map <string, int> &promedioDiario, vector<Registry> datos){
    map<string, int> conexionesDia = connectionsPerDay(date, datos); 
    map<string, int>::iterator it;

    for (it = conexionesDia.begin(); it != conexionesDia.end(); it++ ){
        tree.insertNode(it -> first, it -> second);
    }
    cout << endl << "El top " << n << " del día " << date.tm_mday << "/" << date.tm_mon+1 << "/" << date.tm_year+1900 << " es:" << endl;
    tree.printKth(n); 

    map<string, int> conexionesTemp;
    tree.saveKth(n, conexionesTemp);

    for (map<string, int>::iterator i = conexionesTemp.begin(); i!=conexionesTemp.end(); ++i){
        if (i -> second > 1){ i -> second = 1; }
        i -> second += numeroDeOcurrencias[i -> first];
    }
    tree.saveKth(n, promedioDiario);

    for (map<string, int>::iterator i = promedioDiario.begin(); i!=promedioDiario.end(); ++i){
        i->second += conexionesTemp[i->first];        
    }

    numeroDeOcurrencias = conexionesTemp;
}

/*
Obtinene un set de las fechas de las conexiones
O(n)

Return set of dates
*/
set<Date> obtenerFechas(vector<Registry> datos){
    set<Date> todasLasFechas;
    for(int i = 0; i<datos.size(); i++){
        Date d(datos[i].date);
            todasLasFechas.insert( d );
    }

    return todasLasFechas;
}

int main(void){
    Reader r; 
    vector <Registry> datos = r.readFile(); 
    map<string, CompConnections> computadoras;
    // Utiliza estas funciones para imprimir por cada día de las bitácoras el top 5
    //Imprimir top 5 por día
    set<Date> todasLasFechas = obtenerFechas(datos);
    map<string, int> numeroDeOcurrencias;
    map<string, int> promedioDiario;

    for (set<Date>::iterator it = todasLasFechas.begin(); it != todasLasFechas.end(); ++it){
        BinarySearchTree tops; 
        top(tops,5,it->date, numeroDeOcurrencias, promedioDiario, datos); 
    }

    cout << "RESPUESTAS" << endl; 
    cout << "1. ¿Existe algún sitio que se mantenga en el top 5 en todos los días?" << endl;
    cout << "Se mantuvieron en el top 5 diario: " << endl; 

    for(map<string, int>::iterator it = numeroDeOcurrencias.begin(); it != numeroDeOcurrencias.end(); ++it){
        if(it->second == todasLasFechas.size()){
            cout<<"\t"<<it->first<<"\t: "<<it->second<<endl;
        }
    }

    cout << "2. ¿Existe algún sitio que entre al top 5 a partir de un día y de ahí aparezca en todos los días subsecuentes?" << endl;
    cout << "Se mantuvieron en el top 5: " << endl;

    for(map<string, int>::iterator it = numeroDeOcurrencias.begin(); it != numeroDeOcurrencias.end(); ++it){    
        if(it->second > 1){
            cout<<"\t"<<it->first<<"\t : se mantuvo "<<it->second<< " días"<<endl;
        }
    }

    cout << "3. ¿Existe algún sitio que aparezca en el top 5 con una cantidad más alta de tráfico que lo normal?" << endl;
    cout << "\tLos siguientes sitios tienen una cantidad de tráfico notable: " << endl; 
    
    for(map<string, int>::iterator it = promedioDiario.begin(); it != promedioDiario.end(); ++it){    
            if ((it->second)/todasLasFechas.size() > 100){
                cout<<"\t"<<it->first<<"\t : "<<it->second<<endl;
            }
    }
    
    return 0;
}