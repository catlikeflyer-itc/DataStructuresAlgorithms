#include <iostream>
using namespace std;

long int factorial(int n)
{
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

int main() 
{
    // Factorial de 5
    cout << factorial(5) << endl;

    return 0;
}