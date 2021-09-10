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