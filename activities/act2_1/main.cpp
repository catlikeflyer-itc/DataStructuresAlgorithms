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
    
    Node<int> newNode(3, NULL); 
    list.sortedInsert(&newNode); 
    list.print(); 
    list.reverse(); 
    list.print(); 
    list.clear(); 
    list.print(); 
    return 0; 
}