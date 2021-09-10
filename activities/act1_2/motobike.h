/**
 * @file motorbike.h
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

class Motorbike: public Car { 
    private:
        int cylinders;

    public: 
        Motorbike();
        Motorbike(int c, string b, string m, int y, float p, int cy);

        void setCylinders(int c){ cylinders = c; };

        int getCylinders(){ return cylinders; };
};

// Default constructor  
Motorbike::Motorbike(): Car(){
    cylinders = 0;
};

// Overloaded constructor
Motorbike::Motorbike(int c, string b, string m, int y, float p, int cy): Car(c, b, m, y, p){
    cylinders = cy;
}
