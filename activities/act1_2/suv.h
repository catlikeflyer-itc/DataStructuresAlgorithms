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
        Suv(int c, string b, string m, int y, float p, string t);

        void setTraction(string t){ traction = t; };

        string getTraction(){ return traction; };
};

// Default constructor
Suv::Suv(): Car(){
    traction = "";
};

// Overloaded constructor
Suv::Suv(int c, string b, string m, int y, float p, string t): Car(c, b, m, y, p){
    traction = t;
}