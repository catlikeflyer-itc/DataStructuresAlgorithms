#include <iostream>
#include <vector>
#include "car.h"
#include "motobike.h"
#include "suv.h"
#include "buyer.h"
using namespace std;

class Sale {
    private:
        vector<Car> soldCars;
        vector<Motorbike> soldBikes;
        vector<Suv> soldSuvs;
        Buyer client;

    public:
        Sale();

        void addCar(Car c){
            soldCars.push_back(c);
        };
        void addBike(Motorbike mb){
            soldBikes.push_back(mb);
        };
        void addSuv(Suv s){
            soldSuvs.push_back(s);
        };
        void setClient(Buyer b){
            client = b;
        }

        vector<Car> getCarsSold(){ return soldCars; };
        vector<Motorbike> getBikesSold(){ return soldBikes; };
        vector<Suv> getSuvsSold(){ return soldSuvs; };
        Buyer getClient(){ return client; };
};