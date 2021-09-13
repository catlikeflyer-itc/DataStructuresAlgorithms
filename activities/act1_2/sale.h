/**
 * @file sale.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef Sale_h
#define Sale_h
#include <iostream>
#include <vector>
#include "car.h"
#include "motobike.h"
#include "suv.h"
#include "buyer.h"
using namespace std;

class Sale {
    private:
        Car soldCar;
        Motorbike soldMotorbike;
        Suv soldSuv;
        Buyer client;

    public:
        Sale(); //default constructor

        void setCar(Car c){
            soldCar = c;
        };

        void setBike(Motorbike mb){
            soldMotorbike = mb;
        };

        void setSuv(Suv s){
            soldSuv = s;
        };

        void setClient(Buyer b){
            client = b;
        };
        
        Car getCarsSold(){ return soldCar; };

        Motorbike getBikesSold(){ return soldMotorbike; };

        Suv getSuvsSold(){ return soldSuv; };

        Buyer getClient(){ return client; };
};

#endif