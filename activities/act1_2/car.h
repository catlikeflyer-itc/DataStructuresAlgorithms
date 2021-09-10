/**
 * @file autos.cpp
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
        string model;
        int year;
        float price;

    public: 
        Car();
        Car(int c, string b, string m, int y, float p);

        void setCode(int c){code = c; };
        void setBrand(string b){ brand = b; };
        void setModel(string m){ model = m; };
        void setYear(int y){ year = y; };
        void setPrice(float p){ price = p; };
        
        int getCode(){ return code; };
        string getBrand(){ return brand; };
        string getModel(){ return model; };
        int getYear(){ return year; };
        float getPrice(){ return price; };
};


// Default constructo
Car::Car(){
    code = 0;
    brand = "";
    model = "";
    year = 0;
    price = 0.0;
};

// Constructor overload
Car::Car(int c, string b, string m, int y, float p){
    code = c;
    brand = b;
    model = m;
    year = y;
    price = p;
};