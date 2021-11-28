#include <iostream>
#include <vector>
#include <string.h>

/* Función Fibonacci con una tabla temporal */
int fibonacciTabla(int n)
{
    /* Definir una tabla temporal */
    std::vector<int> tabla(10);
    
    tabla[0] = 0;
    tabla[1] = 1;
    
    for (int i = 2; i <= n; ++i) {
        tabla[i] = tabla[i-1] + tabla[i-2];
    }
    
    return tabla[n];
}

int fibonacciIterativo(int n)
{
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else {
        /* Definir variables temporales */
        int n_2 = 0;
        int n_1 = 1;
        
        for (int i = 2; i <= n; ++i) {
            int temp = n_1;
            n_1 = temp + n_2;
            n_2 = temp;
        }
        
        return n_1;
    }
    
    return 0;
}

int fibonacciRecursivo(int n)
{
    /* Condición de parada */
    if (n < 2) {
        return n;
    }
    /* Paso recursivo */
    else {
        return fibonacciRecursivo(n-1) + fibonacciRecursivo(n-2);
    }
}

int main(int argc, const char * argv[])
{
    int num = atoi(argv[1]);
    char op = toupper(argv[2]);

    switch (op) {
        case "r":
            fibonacciRecursivo(num);
            break;
        case "t":
            fibonacciTabla(num);
            break;
        case "i":
            fibonacciTabla(num);
            break;
    }
}