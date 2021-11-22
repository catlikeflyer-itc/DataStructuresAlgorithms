#include <iostream>
#include <vector>
#include <map>
#include "reader.hpp"
#include "compConnections.hpp"
#include <set>
#include <cwctype> 
#include <ctime>
#include <string>
#include "graph.hpp"

using namespace std;

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
        

        string toString(){
            return to_string(this->date.tm_mday) + "/" + to_string(this->date.tm_mon+1) + "/" + to_string(this->date.tm_year+1900);
        }

};

// Imprimir vectores
void print_vector(vector<Registry> arr){
    for (int i = 0; i < arr.size(); i++) arr[i].print();
    cout << endl;
};

// Búsqueda secuencial
int busquedaSecuencial( vector<Registry> d, bool (*condicion)(Registry r) ){
    for(int i = 0; i<d.size(); i++){
        if( condicion(d[i]) ) return i;
    }
    return -1;
}
// Busqueda secuencial (sobrecarga)
int busquedaSecuencial( vector<Registry> d, bool (*condicion)(Registry a, Registry b), Registry r ){
    for(int i = 0; i<d.size(); i++){
        if( condicion(d[i], r) ) return i;
    }
    return -1;
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
    string IPBase = "172.26.89.0";
    // 172.26.89.0 == 172.26.89.142
    for(int i=0; i<10; i++){
        if( IPBase[i] != IPInput[i] ) return false;
    }
    return true; 
}

string encontrarAnomalos(map<string, CompConnections> computadoras){
    map<string, CompConnections>::iterator it;
    for(it = computadoras.begin(); it != computadoras.end(); it++){
        if( esAnomalo( it->second.name ) ) return it->first;
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

    map<string, CompConnections>::iterator it;
    int n = 0;
    for(it = computadoras.begin(); it != computadoras.end(); it++ ){
        if( it->second.name.find(".reto.com") == string::npos /*no lo encontró*/ ){
            n++;
            // Convertir a vector para poder acceder los índices de manera más fácil ;D
            vector<Connection> conexionesV {begin(it->second.inConnections), end(it->second.inConnections)};
            set<string> nombresPorComputadoraUnicos;

            for(int i=0; i< conexionesV.size(); i++ ){
                if ( conexionesV[i].port != 67 ){
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
map<string, int> conexionesPorDia(tm date, vector<Registry> datos){
    map<string, int> numeroDeOcurrencias; 
    for (int i = 0; i < datos.size(); i++){
        if(datos[i].date.tm_mday == date.tm_mday && datos[i].date.tm_mon == date.tm_mon && datos[i].date.tm_year == date.tm_year){ 
            if(datos[i].destinationName.find(".reto.com") == string::npos && datos[i].destinationName.find("-")== string::npos){
                numeroDeOcurrencias[datos[i].destinationName]++; 
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


set<Date> obtenerFechas(vector<Registry> datos){
    set<Date> todasLasFechas;
    for(int i = 0; i<datos.size(); i++){
        Date d(datos[i].date);
            todasLasFechas.insert( d );
    }
    return todasLasFechas;
}


void llenarComputadoras(map<string, CompConnections> &computadoras, vector<Registry> datos){
    for(size_t i=0; i<datos.size(); i++){
        // Correr si la IP origen no está en el map
        if( datos[i].sourceIp != "-" && computadoras.find(datos[i].sourceIp) == computadoras.end() ){
            CompConnections c(datos[i].sourceIp, datos[i].sourceName);
            c.fill(datos);
            computadoras.insert(pair<string,CompConnections>(datos[i].sourceIp,c));
        }
        // Correr si la IP destino no está en el map
        if( datos[i].destinationIp != "-" && computadoras.find(datos[i].destinationIp) == computadoras.end()){
            CompConnections c(datos[i].destinationIp, datos[i].destinationName);
            c.fill(datos);
            computadoras.insert(pair<string,CompConnections>(datos[i].destinationIp,c));
        }
    }
}


void conexionesDiariasEnGrafos( map<Date, Graph<string> > &grafosPorDia, set<Date> todasLasFechas, string IP_A, map<Date, int> &conexionesEntrantesPorDia,  map<Date, int> &conexionesSalientesPorDia, map<string, CompConnections> todasLasComputadoras){
    // Iterar por cada día y hacer grafo
    for (set<Date>::iterator hoy = todasLasFechas.begin(); hoy != todasLasFechas.end(); ++hoy){
        Graph<string> grafo_i;
        // Iterar todas las computadoras para añadir nodos
        for(map<string, CompConnections>::iterator computadora = todasLasComputadoras.begin(); computadora != todasLasComputadoras.end(); ++computadora){
            // Si es interna, añadir al grafo
            if(esInterna(computadora->first)){
                grafo_i.add_node(computadora->first);
            }
        }
        // Iterar todas las computadoras para añadir edges
        for(map<string, CompConnections>::iterator computadora = todasLasComputadoras.begin(); computadora != todasLasComputadoras.end(); ++computadora){
            string i_ip = computadora->first;
            list<Connection> i_conexionesSalientes = computadora->second.outConnections;
            // Iterar todas las conexiones salientes
            for(list<Connection>::iterator conexion = i_conexionesSalientes.begin(); conexion != i_conexionesSalientes.end(); ++conexion){
                // Si es interna, agregar conexion
                if( esInterna(conexion->IP) && (conexion->date == *hoy) ){
                    grafo_i.add_edge_element(i_ip, conexion->IP);
                    // Si destino  == IP_A, entonces guardar en map<Date, int>
                    if(conexion->IP == IP_A){
                        conexionesEntrantesPorDia[*hoy]++;
                    }
                    if(i_ip == IP_A){
                        conexionesSalientesPorDia[*hoy]++;
                    }
                }
            }
        }
        grafosPorDia[*hoy] = grafo_i;
    }
 }

 //Obtener IP con más conexiones por día
 map<Date, string> maxConexionesPorDia(map<Date, Graph<string> > grafosPorDia){
    map<Date, string> maxConexionesPorDia; 
    for(map<Date, Graph<string> >::iterator it = grafosPorDia.begin(); it != grafosPorDia.end(); ++it){
        Graph<string> grafo_hoy = it->second;
        
        map<string, int> numeroDeConexiones = grafo_hoy.saveNeigbhors();
        string ipConMasConexiones = "";
        int maxConexiones = 0;

        // Iterar ips en mapa de cantidad de ocurrencias diarias
        for(map<string, int>::iterator ips = numeroDeConexiones.begin(); ips != numeroDeConexiones.end(); ++ips){
            if(ips->second >= maxConexiones){
                ipConMasConexiones = ips->first;
                maxConexiones = ips->second;
            }
        }
        maxConexionesPorDia[it->first] = ipConMasConexiones;
    }
    return maxConexionesPorDia; 
}

void esVerticeConMasConexionesSalientes(map<Date, string> maxConexionesPorDia, string ipA){
    for(map<Date, string>::iterator it = maxConexionesPorDia.begin(); it != maxConexionesPorDia.end(); ++it){
        
        Date hoy = it->first;
        cout << hoy.toString() << ":\t" << (it->second == ipA ? "Sí": "No") << endl; 
        
    }
}

bool esWeb(Connection c){ 
    if(c.port == 443){
        return true;
    }
    return false;
}

void conexionesWebEnGrafo(map<Date, Graph<string> > &grafosPorDiaWeb, set<Date> todasLasFechas, string IP_i, map<Date, int> &conexionesEntrantesPorDiaWeb, map<string, CompConnections> todasLasComputadoras){
    for (set<Date>::iterator hoy = todasLasFechas.begin(); hoy != todasLasFechas.end(); ++hoy){
        Graph<string> grafo_i;
        conexionesEntrantesPorDiaWeb[*hoy] = 0;
        // Iterar todas las computadoras para añadir nodos
        for(map<string, CompConnections>::iterator computadora = todasLasComputadoras.begin(); computadora != todasLasComputadoras.end(); ++computadora){
            grafo_i.add_node(computadora->first);
        }
        // Iterar todas las computadoras para añadir edges
        for(map<string, CompConnections>::iterator computadora = todasLasComputadoras.begin(); computadora != todasLasComputadoras.end(); ++computadora){
            string i_ip = computadora->first;
            list<Connection> i_conexionesSalientes = computadora->second.outConnections;
            // Iterar todas las conexiones salientes
            // Si es web, agregar conexion
            for(list<Connection>::iterator conexion = i_conexionesSalientes.begin(); conexion != i_conexionesSalientes.end(); ++conexion){
                if( esWeb(*conexion) && (conexion->date == *hoy)){
                    grafo_i.add_edge_element(i_ip, conexion->IP);
                    if(conexion->IP == IP_i){
                        conexionesEntrantesPorDiaWeb[*hoy]++;
                    }
                }
            }
        }
        grafosPorDiaWeb[*hoy] = grafo_i;
    }
}


int main(void){
    Reader r; 
    vector <Registry> datos = r.readFile(); 
    map<string, CompConnections> todasLasComputadoras;
    llenarComputadoras(todasLasComputadoras, datos);

    // Una ip interna, que llamaremos A, la cual se comunica con algunas otras computadoras internas.
    string IP_INTERNA_A = "172.26.89.118"; //Jennifer
    CompConnections A = todasLasComputadoras[IP_INTERNA_A];

    // Sitio con nombre anómalo
    string IP_ANOMALA_B = encontrarAnomalos(todasLasComputadoras); 
    CompConnections B = todasLasComputadoras[IP_ANOMALA_B];
    // Sitio con mucho tráfico en un día
    string IP_TRAFICO_C = "64.158.210.175"; //Groupon que tuvo más de 400 visitas en un día
    CompConnections C = todasLasComputadoras[IP_TRAFICO_C];

    /* 1. Utilizando un grafo con las conexiones entre las ip de la red interna, 
    determina la cantidad de computadoras con las que se ha conectado A por día. 
    ¿Es A el vértice que más conexiones salientes hacia la red interna tiene? */
    map<Date, Graph<string> > grafosPorDia;
    set<Date> todasLasFechas = obtenerFechas(datos);
    map<Date, int> conexionesEntrantesPorDia;
    map<Date, int> conexionesSalientesPorDia;
    conexionesDiariasEnGrafos(grafosPorDia, todasLasFechas, IP_INTERNA_A, conexionesEntrantesPorDia, conexionesSalientesPorDia, todasLasComputadoras); 
    
    cout<<"1. Utilizando un grafo con las conexiones entre las ip de la red interna, determina la cantidad de computadoras con las que se ha conectado A por día."<<endl;
    for(map<Date, int>::iterator it = conexionesSalientesPorDia.begin(); it != conexionesSalientesPorDia.end(); ++it){
        Date hoy = it->first;
        cout<<hoy.toString()<<":\t"<<it->second<<endl;
    }
    cout << "¿Es A el vértice que más conexiones salientes hacia la red interna tiene?" << endl; 
    map<Date, string> maxConexionesDia = maxConexionesPorDia(grafosPorDia); 
    esVerticeConMasConexionesSalientes(maxConexionesDia, IP_INTERNA_A);
    
    /* 2. Utilizando el grafo del punto anterior, ubica la cantidad de computadoras que se han conectado hacia A por día.
    ¿Existen conexiones de las demás computadoras hacia A? */
    cout<<"2. Utilizando el grafo del punto anterior, ubica la cantidad de computadoras que se han conectado hacia A por día. ¿Existen conexiones de las demás computadoras hacia A?"<<endl;
    for(map<Date, int>::iterator it = conexionesEntrantesPorDia.begin(); it != conexionesEntrantesPorDia.end(); ++it){
        Date hoy = it->first;
        cout<<hoy.toString()<<":\t"<<it->second<<endl;
    }
    cout << "Sí existen conexiones entrantes a la computadora con IP: " << IP_INTERNA_A << endl; 
    
   /* 3. Utilizando el mismo grafo del punto anterior, indica cuántas computadoras 
    se han conectado a C por día */
    map<Date, Graph<string> > grafosPorDiaWeb;
    map<Date, int> conexionesEntrantesPorDiaWeb;
    conexionesWebEnGrafo(grafosPorDiaWeb, todasLasFechas, IP_ANOMALA_B, conexionesEntrantesPorDiaWeb, todasLasComputadoras); 
    cout << "3. Utilizando un grafo de conexiones a sitios web, determina cuántas computadoras se han conectado a B por día." << endl; 
    for(map<Date, int>::iterator it = conexionesEntrantesPorDiaWeb.begin(); it != conexionesEntrantesPorDiaWeb.end(); ++it){
        Date hoy = it->first;
        cout<<hoy.toString()<<":\t"<<it->second<<endl;
    }

    /* Utilizando el mismo grafo del punto anterior, 
    indica cuántas computadoras se han conectado a C por día.
    */
    conexionesWebEnGrafo(grafosPorDiaWeb, todasLasFechas, IP_TRAFICO_C, conexionesEntrantesPorDiaWeb, todasLasComputadoras); 
    cout << "4. Utilizando el mismo grafo del punto anterior, indica cuántas computadoras se han conectado a C por día." << endl; 
    for(map<Date, int>::iterator it = conexionesEntrantesPorDiaWeb.begin(); it != conexionesEntrantesPorDiaWeb.end(); ++it){
        Date hoy = it->first;
        cout<<hoy.toString()<<":\t"<<it->second<<endl;
    }
    return 0;
}