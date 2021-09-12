/**
 * @file suv.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include "car.h"
using namespace std;
 
class Suv: public Car { 
    private:
        string traction;
    
    public: 
        Suv();
        Suv(int c, string b, int y, float p, float k, string t);

        void setTraction(string t){ traction = t; };

        string getTraction(){ return traction; };

        void print();
};

// Default constructor
Suv::Suv(): Car(){
    traction = "";
};

// Overloaded constructor
Suv::Suv(int c, string b, int y, float p, float k, string t): Car(c, b, y, p, k){
    traction = t;
}

void Suv::print(){
    std::cout << "--- Vehiculo ---" << std::endl;
    std::cout << "Modelo: " << brand << " " << year << "\tCodigo: " << code << std::endl;
    std::cout << "Traccion: " << traction << "\tKilometraje: " << km << "Precio: $" << price << std::endl;
}