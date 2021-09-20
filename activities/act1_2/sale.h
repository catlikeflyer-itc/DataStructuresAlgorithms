/**
 * @file sale.h
 * @Emiliano Cabrera A01025453, Do Hyun Nam A01025276
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

/*
Class that stores a sale made by the dealership, with each sale having 
the vehicles sold and to whom they were sold to as attributes. The attributes are made 
up by the Car class and its childres, as well as the Buyer class.
*/
class Sale {
    private:
        Car soldCar;
        Motorbike soldMotorbike;
        Suv soldSuv;
        Buyer client;

    public:
        Sale(); 
        
        // Setters
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
        
        // Getters
        Car getCarsSold(){ return soldCar; };
        Motorbike getBikesSold(){ return soldMotorbike; };
        Suv getSuvsSold(){ return soldSuv; };
        Buyer getClient(){ return client; };
};

#endif