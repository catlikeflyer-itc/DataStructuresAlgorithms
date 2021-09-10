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

class Motorbike: public Car { 
    private:
        int cylinders;

    public: 
        Motorbike();
        Motorbike(int c, string b, string m, int y, int cy);

        void setCylinders(int c){ cylinders = c; };

        int getCylinders(){ return cylinders; };
};

Motorbike::Motorbike(): Car(){
    cylinders = 0;
};

Motorbike::Motorbike(int c, string b, string m, int y, int cy): Car(c, b, m, y){
    cylinders = cy;
}
