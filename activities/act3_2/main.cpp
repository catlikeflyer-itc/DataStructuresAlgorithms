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
#include "reader.hpp"
#include "compConnections.hpp"
#include <set>
#include <cwctype> 
#include <ctime>
#include <string>
#include "bst.hpp"
using namespace std;

class Date{
    public:
        tm date;
        Date( tm date ){
            this -> date = date;
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
            return to_string(this -> date.tm_mday) + "/" + to_string(this -> date.tm_mon + 1) + "/" + to_string(this -> date.tm_year + 1990);
        }

};

// Imprimir vectores
void print_vector(vector<Registry> arr){
    for (int i = 0; i < arr.size(); i++) arr[i].print();
    cout << endl;
};

// Búsqueda secuencial
int sequentialSearch( vector<Registry> d, bool (*condition)(Registry r) ){
    for (int i = 0; i < d.size(); i++){
        if (condition(d[i]) ) return i;
    }
    return -1;
}
// Busqueda secuencial (overload)
int sequentialSearch( vector<Registry> d, bool (*condition)(Registry a, Registry b), Registry r ){
    for (int i = 0; i<d.size(); i++){
        if (condition(d[i], r) ) return i;
    }
    return -1;
}

