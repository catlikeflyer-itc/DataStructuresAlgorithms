/**
 * @file car.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
using namespace std;
 
class Car {
    protected:
        int code;
        string brand;
        int year;
        float price;
        float km;

    public: 
        Car();
        Car(int c, string b, int y, float p, float k);

        void setCode(int c){code = c; };
        void setBrand(string b){ brand = b; };
        void setYear(int y){ year = y; };
        void setPrice(float p){ price = p; };
        void setKm(float k){ km = k; };
        
        int getCode(){ return code; };
        string getBrand(){ return brand; };
        int getYear(){ return year; };
        float getPrice(){ return price; };
        float getKm(){ return km; };

        void print();
};

// Default constructor
Car::Car(){
    code = 0;
    brand = "";
    year = 0;
    price = 0.0;
    km = 0.0;
};

// Constructor overload
Car::Car(int c, string b, int y, float p, float k){
    code = c;
    brand = b;
    year = y;
    price = p;
    km = k;
};

void Car::print(){
    std::cout << "--- Vehiculo ---" << std::endl;
    std::cout << "Modelo: " << brand << " " << year << "\tCodigo: " << code << std::endl;
    std::cout << "Kilometraje: " << km << "Precio: $" << price << std::endl;
}