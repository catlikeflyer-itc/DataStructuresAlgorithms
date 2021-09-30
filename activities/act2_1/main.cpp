/**
 * Main file
 * main.cpp
 * Emiliano Cabrera A01025453  , Do Hyun Nam A01025276
 * 
 */
#include "linkedList.hpp"
#include <iostream>

int main(){
    std::cout << "Creating example list" << std::endl;
    LinkedList<int> list; 
    list.addLast(5);
    list.addLast(5);
    list.addLast(4);
    list.addLast(4); 
    list.addLast(4);
    list.addLast(3); 
    list.addLast(3); 
    list.addLast(2); 
    list.addLast(2); 
    list.addLast(1);
    list.addLast(1);
    list.addLast(1);
    list.addLast(1);
    list.addLast(1); 
    list.print();

    std::cout << "Checking count of 4s" << std::endl;
    list.count(4); 

    std::cout << "Remove duplicates" << std::endl;
    list.removeDuplicates(); 
    list.print(); 

    // Sublist test
    std::cout << "Creating sublist" << std::endl;
    LinkedList<int> sublist = list.subList(2, 3);
    sublist.print();

    // Delete range test
    std::cout << "Deleting range from list" << std::endl;
    list.deleteRange(2, 3);
    list.print();

    // Creating new LinkedList, B
    LinkedList<int> B;
    B.addLast(4);
    B.addLast(6);
    B.addLast(8);
    B.addLast(1); 
    B.addLast(1);
    B.addLast(3); 
    B.addLast(4);
    B.addLast(4); 
    list.print();

    // Union
    LinkedList<int> * u_list = list.unionn(&B);
    u_list->print();

    //Intersection
    LinkedList<int> * i_list = list.intersection(&B);
    i_list->print();

    //Except
    LinkedList<int> * e_list = list.except(&B);
    e_list->print();
    
    Node<int> newNode(3, NULL); 
    list.sortedInsert(&newNode); 
    list.print(); 
    list.reverse(); 
    list.print(); 
    list.clear(); 
    list.print(); 
    return 0; 
}