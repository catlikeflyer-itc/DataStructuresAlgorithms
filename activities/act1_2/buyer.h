/**
 * @file buyer.h
 * @Emiliano Cabrera A01025453, Do Hyun Nam A01025276
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef Buyer_h
#define Buyer_h
#include <iostream>
using namespace std;

class Buyer {
    private:
        string surname;
        string name;
        string ine;
    
    public:
        Buyer();
        Buyer(string sn, string n, string i);

        void setSurname(string sn){ surname = sn; };
        void setName(string n){ name = n; };
        void setIne(string i){ ine = i; };
    
        string getSurname(){ return surname; };
        string getName(){ return name; };
        string getIne(){ return ine; };

        void print();
};

Buyer::Buyer() {
    surname = "Doe";
    name = "John";
    ine = "00aa00aa00aa";
}

Buyer::Buyer(string sn, string n, string i) {
    surname = sn;
    name = n;
    ine = i;
}

void Buyer::print(){
    std::cout << "--- Cliente ---" << std::endl;
    std::cout << name << " " << surname << "\tINE: " << ine << std::endl;
}

#endif
