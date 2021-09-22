#include <iostream>

int main(int argc, const char * argv[]) {
    
    /* Declarar variables enteras y un apuntador */
    int i, j, *p;
    /* Direccion de memoria de i */
    p = &i;

    std::cout << "Direccion de i: " << p << std::endl;
    
    *p = 10; // i = 10
    
    std::cout << "Valor de i: " << i << std::endl;

    p = &j;

    std::cout << "Direccion de j: " << p << std::endl;

    *p = -2; // j = -2

    std::cout << "Valor de j: " << j << std::endl;

    return 0;
    
}