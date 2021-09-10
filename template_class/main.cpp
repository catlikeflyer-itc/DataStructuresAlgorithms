#include <iostream>
#include "array.cpp"
using namespace std;

int main(void) 
{
    Array <double>data(10);
    int i; 
    double val;

    for (i=0; i<10; i++) 
    {
        if(!data.setData(i, i/10.0))
            cout << "Failed to set data" << endl;
        
        if(!data.getData(i, val))
            cout << "Failed to get data" << endl;
        else 
            cout << "Added " << val << endl;
    }

    return 0;
}