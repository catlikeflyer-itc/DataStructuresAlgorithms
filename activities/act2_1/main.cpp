/**
 * Main file
 * main.cpp
 * Emiliano Cabrera A01025453  , Do Hyun Nam A01025276
 * 
 */
#include "linkedList.hpp"
#include <iostream>

int main(){
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
    list.count(4); 
    list.removeDuplicates(); 
    list.print(); 

    LinkedList<int> sublist = list.subList(2, 3);
    sublist.print();

    
    Node<int> newNode(3, NULL); 
    list.sortedInsert(&newNode); 
    list.print(); 
    list.reverse(); 
    list.print(); 
    list.clear(); 
    list.print(); 
    return 0; 
}