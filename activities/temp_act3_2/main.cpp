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
        Date( tm date ){
            this->date = date;
            // this->date.tm_mday = date.tm_mday;
            // this->date.tm_mon = date.tm_mon; 
            // this->date.tm_year = date.tm_year; 
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
        

        string toString(){
            return to_string(this->date.tm_mday) + "/" + to_string(this->date.tm_mon+1) + "/" + to_string(this->date.tm_year+1990);
        }

};

// Imprimir vectores
void print_vector(vector<Registro> arr){
    for (int i = 0; i < arr.size(); i++) arr[i].print();
    cout << endl;
};

// Búsqueda secuencial
int busquedaSecuencial( vector<Registro> d, bool (*condicion)(Registro r) ){
    for(int i = 0; i<d.size(); i++){
        if( condicion(d[i]) ) return i;
    }
    return -1;
}
// Busqueda secuencial (sobrecarga)
int busquedaSecuencial( vector<Registro> d, bool (*condicion)(Registro a, Registro b), Registro r ){
    for(int i = 0; i<d.size(); i++){
        if( condicion(d[i], r) ) return i;
    }
    return -1;
}


void agregarNoRetoASet(set<string> s, vector<Registro> datos){
    for(int i=0; i<5000; i++){
        if(datos[i].fuente_hostname.find(".reto.com") || datos[i].fuente_hostname.find("-") ){
            s.insert(datos[i].fuente_hostname); 
        }
    }
}

void llenarComputadoras(map<string, ConexionesComputadora> &computadoras, vector<Registro> datos){
    // throwback a nuestro debugging de una hora, porque no estábamos editando el map original :)
    for(int i=0; i<6000; i++){ //Cambiar a datos.size()
        ConexionesComputadora c(datos[i].fuente_ip, datos[i].fuente_hostname);
        c.llenar(datos);
        computadoras.insert(pair<string,ConexionesComputadora>(datos[i].fuente_ip,c));
    }
}

void agregarNoRetoASetyLlenarComputadoras(set<string> s, map<string, ConexionesComputadora> &computadoras, vector<Registro> datos){
    for(size_t i=0; i<datos.size(); i++){
        if(datos[i].fuente_hostname.find(".reto.com") || datos[i].fuente_hostname.find("-") ){
            s.insert(datos[i].fuente_hostname); 
        }
        // Correr si la IP origen no está en el map
        if( datos[i].fuente_ip != "-" && computadoras.find(datos[i].fuente_ip) == computadoras.end() ){
            ConexionesComputadora c(datos[i].fuente_ip, datos[i].fuente_hostname);
            c.llenar(datos);
            computadoras.insert(pair<string,ConexionesComputadora>(datos[i].fuente_ip,c));
        }
        // Correr si la IP destino no está en el map
        if( datos[i].destino_ip != "-" && computadoras.find(datos[i].destino_ip) == computadoras.end()){
            ConexionesComputadora c(datos[i].destino_ip, datos[i].destino_hostname);
            c.llenar(datos);
            computadoras.insert(pair<string,ConexionesComputadora>(datos[i].destino_ip,c));
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

string encontrarAnomalos(map<string, ConexionesComputadora> computadoras){
    map<string, ConexionesComputadora>::iterator it;
    for(it = computadoras.begin(); it != computadoras.end(); it++){
        if( esAnomalo( it->second.nombre ) ) return it->first;
    }
    return "";
}


int computadorasConConexionesEntrantes(map<string, ConexionesComputadora> computadoras){ 
    int n = 0;
    map<string, ConexionesComputadora>::iterator it;
    for(it = computadoras.begin(); it != computadoras.end(); it++ ){
        if(it->second.nombre.find("reto.com") != string::npos && it->second.conexionesEntrantes.size() >= 1) n++;
    }
    return n;
} 

set<string> obtenerIPsEntrantes(map<string, ConexionesComputadora> computadoras) {
    /**
     * - for computadora in computadoras
     * -    si computadora.IP != server.reto.com
     *          iterar por numeroDeOcurrencias entrantes
     *              si conexionEntrante.puerto != 67
     *                  agregar IP al set (para que no se repita :))
     * regresar set
     * Los mensajes DHCP utilizan el puerto 67 (UDP) como puerto del servidor
    */
    set<string> ipsUnicas;

    map<string, ConexionesComputadora>::iterator it;
    int n = 0;
    for(it = computadoras.begin(); it != computadoras.end(); it++ ){
        if( it->second.nombre.find(".reto.com") == string::npos /*no lo encontró*/ ){
            n++;
            // Convertir a vector para poder acceder los índices de manera más fácil ;D
            vector<Conexion> conexionesV{begin(it->second.conexionesEntrantes), end(it->second.conexionesEntrantes) };
            set<string> nombresPorComputadoraUnicos;
            for(int i=0; i< conexionesV.size(); i++ ){
                if ( conexionesV[i].puerto != 67 ){
                    nombresPorComputadoraUnicos.insert(conexionesV[i].host);
                    ipsUnicas.insert( conexionesV[i].IP );
                }
            }
        }
    }

   return ipsUnicas; 
}

/*
conexionesPorDia
Recibe una fecha 
Regresa un map<string, int>
Conteniendo la cantidad de numeroDeOcurrencias entrantes a cada sitio/página que no sea "-" 
y que no pertenezca al dominio "reto.com" del día especificado por la fecha de entrada. 
*/
map<string, int> conexionesPorDia(tm date, vector<Registro> datos){
    map<string, int> numeroDeOcurrencias; 
    for (int i = 0; i < datos.size(); i++){
        if(datos[i].fecha.tm_mday == date.tm_mday && datos[i].fecha.tm_mon == date.tm_mon && datos[i].fecha.tm_year == date.tm_year){ 
            if(datos[i].destino_hostname.find(".reto.com") == string::npos && datos[i].destino_hostname.find("-")== string::npos){
                numeroDeOcurrencias[datos[i].destino_hostname]++; 
            }
        }
    }
    return numeroDeOcurrencias; 
}
// Imprime un mapa
void printMap(map<string, int> numeroDeOcurrencias){
    map<string, int>::iterator it;
    for(it = numeroDeOcurrencias.begin(); it != numeroDeOcurrencias.end(); it++ ){
        cout<< it->first <<":\t" << it->second <<endl;
    }
}

/*
Contenga una función llamada top, la cual recibe un parámetro n de tipo int 
y una fecha. Esta función debe imprimir los n sitios con más accesos en esa fecha. 
Para ello, puedes usar la función conexionesPorDia y debes agregar los sitios a un 
BST utilizando como parámetro de ordenamiento la cantidad de numeroDeOcurrencias entrantes.
*/
void top(
    BinarySearchTree &tree, int n, tm date, map<string, int> &numeroDeOcurrencias, map <string, int> &promedioDiario, vector<Registro> datos){
    map<string, int> conexionesDia = conexionesPorDia(date, datos); 
    map<string, int>::iterator it;
    for(it = conexionesDia.begin(); it != conexionesDia.end(); it++ ){
        tree.insertNode(it->first, it->second);
    }
    cout << endl << "El top " << n << " del día " << date.tm_mday << "/" << date.tm_mon+1 << "/" << date.tm_year+1900 << " es:" << endl;
    tree.printKth(n); 

    map<string, int> conexionesTemp;
    tree.saveKth(n, conexionesTemp);

    for(map<string, int>::iterator i = conexionesTemp.begin(); i!=conexionesTemp.end(); ++i){
        if(i->second > 1){ i->second = 1; }
        i->second += numeroDeOcurrencias[i->first];
    }
    tree.saveKth(n, promedioDiario);
    for(map<string, int>::iterator i = promedioDiario.begin(); i!=promedioDiario.end(); ++i){
        i->second += conexionesTemp[i->first];        
    }

    numeroDeOcurrencias = conexionesTemp;
}

set<Date> obtenerFechas(vector<Registro> datos){
    set<Date> todasLasFechas;
    for(int i = 0; i<datos.size(); i++){
        Date d(datos[i].fecha);
            todasLasFechas.insert( d );
    }
    return todasLasFechas;
}





int main(void){
    Reader r; 
    vector <Registro> datos = r.readFile(); 
    map<string, ConexionesComputadora> computadoras;
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