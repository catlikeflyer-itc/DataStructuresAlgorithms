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
#include "car.h"
using namespace std;
 
class Suv: public Car { 
    private:
        string traction;
    
    public: 
        Suv();
        Suv(int c, string b, string m, int y, string t);

        void setTraction(string t){ traction = t; };

        string getTraction(){ return traction; };
};

Suv::Suv(): Car(){
    traction = "";
};

Suv::Suv(int c, string b, string m, int y, string t): Car(c, b, m, y){
    traction = t;
}