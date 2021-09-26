/**
 * Linked List Type
 * linkedList.hpp
 * Emiliano Cabrera A010  , Do Hyun Nam A01025276
 * 
 */
#ifndef linkedList_hpp
#define linkedList_hpp
#include <iostream>
#include <vector>
#include <stddef.h> // To enable use of NULL
#include "node.hpp"

template<class T>
class LinkedList {
    protected:
        Node<T> *head;
    
    public:
        LinkedList() {
            head = NULL;
            int size;
        }

        bool isEmpty() { return size == 0; }; // Checks if linked list is empty

        void addFirst(T data);
        void addLast(T data);
        
        bool deleteData(T data);
        bool deleteAt(int data);
        
        T getData(int i); 
        
        bool updateAt(int i, T data);
        bool updateData(T prevData, T newData);

        void print();

        // Methods for homework
        int count(T searchValue);
        void clear();
        void sortedInsert(Node<T> * newNode);
        void removeDuplicates();
        void reverse();
}

template<class T>
LinkedList<T>::LinkedList(){
    this-> head = NULL;
    this-> size = 0;
}


/*
Adds node and heads it, also receives data
Complexity of O(1)
*/
template<class T>
void LinkedList<T>::addFirst(T data){
    head = new Node<T>(data, head);
    size++; // Increments size count
}

/*
Adds data as last element from a list
Complexity of O(n)
*/
template<class T>
void LinkedList<T>::addLast(T data){
    if (isEmpty()) {
        // If list is empty creates a head with data given
        head = new Node<T>(data);
    } else { 
        // If not empty finds position before next == null to insert data at last position
        while (aux -> next != NULL){
            aux = aux -> next;
        }
        aux -> next = new Node<T>(data);
    }
    size++;
}

/*
Gets data from given node i
Complexity of O(n)
*/
template<class T>
T LinkedList<T>::getData(int i){
    if (!isEmpty() && i > 0 && i <= size) {
        int counter = 1;
        Node<T> *aux = head;

        while (counter <= size) {
            if(counter == i){
                return aux -> data;
            }

            counter++;
            aux = aux -> next;
        }
    }
    throw runtime_error("OUT OF RANGE\n");
}

/*
Updates data at given node i
Complexity of O(n)
*/
template<class T>
bool LinkedList<T>::updateAt(int i, T data_i){
    if (!isEmpty() && i > 0 && i <= size) {
        int count = 1;
        Node<T> *aux = head;

        while (count <= size) {
            if (count == i) {
                aux -> data = data_i;
                std::cout << "UPDATED" << std::endl;

                return true;
            }
            count++;
            aux = aux -> next;
        }
    }
    throw runtime_error("OUT OF RANGE");
}

//updateData
//updates data from given data
//O(n)
/*

*/
template<class T>
bool LinkedList<T>::updateData(T prevData, T newData){//se mueve hasta encontrar el nodo con el data igual al input y reemplaza
    if (!isEmpty()) {
        Node<T> *aux = head;
        int count = 1;

        while (count <= size) {
            if(aux -> data == prevData){
                aux -> data = newData;
                cout << "UPDATED" << endl;

                return true;
            }
            count++;
            aux = aux->next;
        }
    }
    throw runtime_error("NOT FOUND\n");
}

#endif
