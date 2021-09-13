/**
 * @file motobike.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef Motorbike_h
#define Motorbike_h
#include <iostream>
#include "car.h"
using namespace std;

class Motorbike: public Car { 
    private:
        int cylinders;

    public: 
        Motorbike();
        Motorbike(int c, string b, int y, float p, float k, int cy);

        void setCylinders(int c){ cylinders = c; };

        int getCylinders(){ return cylinders; };

        void print();
};

// Default constructor  
Motorbike::Motorbike(): Car(){
    cylinders = 0;
};

// Overloaded constructor
Motorbike::Motorbike(int c, string b, int y, float p, float k, int cy): Car(c, b, y, p, k){
    cylinders = cy;
}

void Motorbike::print(){
    std::cout << "--- Vehiculo ---" << std::endl;
    std::cout << "Modelo: " << brand << " " << year << "\tCodigo: " << code << std::endl;
    std::cout << "Cilindraje: " << cylinders << "\tKilometraje: " << km << "Precio: $" << price << std::endl;
}

#endif