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

    public: 
        Car();
        Car(int c, string b, string m, int y);

        void setCode(int c){code = c; };
        void setBrand(string b){ brand = b; };
        void setModel(string m){ model = m; };
        void setYear(int y){ year = y; };
        
        int getCode(){ return code; };
        string getBrand(){ return brand; };
        string getModel(){ return model; };
        int getYear(){ return year; };
};

Car::Car(){
    code = 0;
    brand = "";
    model = "";
    year = 0;
}

Car::Car(int c, string b, string m, int y){
    code = c;
    brand = b;
    model = m;
    year = y;
}