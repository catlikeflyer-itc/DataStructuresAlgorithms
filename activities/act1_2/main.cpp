/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <sstream>
#include <string>
#include "sale.h"
#include "buyer.h"
#include "search.h"
#include "order.h"

void finalize() // exit function
{
    exit(0);
}

std::vector<std::string> split(std::string line) // name spliting function, returns a vector<string> comprised of [name, surname]
{  
    std::stringstream ss(line); 
    std::string s;
    std::vector<std::string> line_vec;
 
    while(std::getline(ss, s, ' ')) 
    { 
        line_vec.push_back(s); 
    }

    return line_vec;
}

int main(){

    // switch and while variables
    bool cont = true;
    bool inner_cont;
    int op;
    char car_op;
    
    // Object variables, inputed by the user
    std::string cliente, marca, ine, trac;
    int code, yy, km, cc;
    float monto;
    
    // main variables, they are the Sales vector, the name vector and the Sale item.
    std::vector<Sale> ventas;
    std::vector<std::string> full_name;
    Sale venta;

    // menu loop
    while(cont != false)
    {
        std::cout << "\t\tSISTEMA DE VENTAS" << std::endl << "[Ingrese el numero de la accion]" << std::endl;
        std::cout << "----------------------------------------" << std::endl << "1.- Ingresar una venta" << std::endl;
        std::cout << "2.- Ver listado de ventas por monto" << std::endl << "3.- Ver todos los vehiculos comprados por un cliente" << std::endl;
        std::cout << "4.- Buscar vehiculos por año y kilometraje" << std::endl << "5.- Salir" << std::endl;
        
        std::cin >> op;
        switch(op)
        {
            case 1: // adding a sale
                std::cout << "Ingrese el nombre del cliente que realiza la compra" << std::endl;
                getline(std::cin, cliente);
                full_name = split(cliente);

                std::cout << "Ingrese el ine del cliente" << std::endl;
                std::cin >> ine;
                
                std::cout << "Ingrese el caracter del tipo de vehiculo que se esta comprando" << std::endl << "\t[ c (coche) , m (motocicleta) , s (SUV) ]" << std::endl;
                std::cin >> car_op;

                inner_cont = true;

                // loop that makes sure a valid vehicle type is input
                while(inner_cont != false)
                {
                    switch(tolower(car_op))
                    {
                        case 'c':
                            std::cout << "Ingrese el codigo del automovil" << std::endl;
                            std::cin >> code;
                            
                            std::cout << "Ingrese la marca del automovil" << std::endl;
                            std::cin >> marca;
                            
                            std::cout << "Ingrese el año del automovil" << std::endl;
                            std::cin >> yy;

                            std::cout << "Ingrese el kilometraje del automovil" << std::endl;
                            std::cin >> km;
                            
                            std::cout << "Ingrese el monto a pagar del automovil" << std::endl;
                            std::cin >> monto;

                            venta.setClient(Buyer(full_name[1], full_name[0], ine));
                            venta.setCar(Car(code,marca,yy,monto,km));

                            ventas.push_back(venta);

                            inner_cont = false;

                            break;

                        case 'm':
                            std::cout << "Ingrese el codigo de la motocicleta" << std::endl;
                            std::cin >> code;
                            
                            std::cout << "Ingrese la marca de la motocicleta" << std::endl;
                            std::cin >> marca;
                            
                            std::cout << "Ingrese el año de la motocicleta" << std::endl;
                            std::cin >> yy;

                            std::cout << "Ingrese el kilometraje de la motocicleta" << std::endl;
                            std::cin >> km;
                            
                            std::cout << "Ingrese el monto a pagar de la motocicleta" << std::endl;
                            std::cin >> monto;

                            std::cout << "Ingrese el cilindraje de la motocicleta" << std::endl;
                            std::cin >> cc;

                            venta.setClient(Buyer(full_name[1], full_name[0], ine));
                            venta.setBike(Motorbike(code,marca,yy,monto,km,cc));

                            ventas.push_back(venta);

                            inner_cont = false;
                            
                            break;

                        case 's':
                            std::cout << "Ingrese el codigo de la camioneta" << std::endl;
                            std::cin >> code;
                            
                            std::cout << "Ingrese la marca de la camioneta" << std::endl;
                            std::cin >> marca;
                            
                            std::cout << "Ingrese el año de la camioneta" << std::endl;
                            std::cin >> yy;

                            std::cout << "Ingrese el kilometraje de la camioneta" << std::endl;
                            std::cin >> km;
                            
                            std::cout << "Ingrese el monto a pagar de la camioneta" << std::endl;
                            std::cin >> monto;

                            std::cout << "Ingrese la traccion de la camioneta" << std::endl;
                            std::cin >> trac;

                            venta.setClient(Buyer(full_name[1], full_name[0], ine));
                            venta.setSuv(Suv(code,marca,yy,monto,km,trac));

                            ventas.push_back(venta);

                            inner_cont = false;
                            
                            break;

                        default:
                            std::cout << "Tipo de vehiculo invalido" << std::endl;
                            break;
                    }
                }

                break;

            case 2: // sales by price
                ventas = Order<Sale>::quickSort(ventas, Order<Sale>::asc); // reorders the sales vector by price

                for(int i = 0; i<ventas.size()-1; i++)
                {
                    // prints
                    Sale item = ventas[i];
                    item.getClient().print();
                    item.getCarsSold().print();
                    item.getBikesSold().print();
                    item.getSuvsSold().print();
                }

                break;

            case 3: // sales by a single client
                std::cout << "Ingrese el nombre del cliente que desea buscar" << std::endl; // name entering and splitting
                getline(std::cin, cliente);
                full_name = split(cliente);

                for(int i = 0; i<ventas.size()-1; i++) // loop that goes through the sales vector
                {
                    Sale item = ventas[i];
                    if(item.getClient().getName() == full_name[0] && item.getClient().getSurname() == full_name[1]) // chscks if the required name is the same
                    {
                        // prints everything
                        item.getClient().print();
                        item.getCarsSold().print();
                        item.getBikesSold().print();
                        item.getSuvsSold().print();
                    }
                }

                break;

            case 4: // sales by year and above a certain mileage
                std::cout << "Ingrese el año que desea buscar" << std::endl;
                std::cin >> yy;

                std::cout << "Ingrese el kilometraje minimo por el cual limitar" << std::endl;
                std::cin >> km;

                for(int i = 0; i<ventas.size()-1; i++) // loop that goes through the sales vector
                {
                    Sale item = ventas[i];
                    if(item.getCarsSold().getYear() == yy)
                    {
                        if(item.getCarsSold().getKm() > km)
                        {
                            item.getClient().print();
                            item.getCarsSold().print();
                        }
                    }
                    if(item.getBikesSold().getYear() == yy)
                    {
                        if(item.getBikesSold().getKm() > km)
                        {
                            item.getClient().print();
                            item.getBikesSold().print();
                        }
                    }
                    if(item.getSuvsSold().getYear() == yy)
                    {
                        if(item.getSuvsSold().getKm() > km)
                        {
                            item.getClient().print();
                            item.getSuvsSold().print();
                        }
                    }
                }

                break;

            case 5: // exit
                cont = false;
                finalize();
                break;

            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
    }
    

    return 0;
}