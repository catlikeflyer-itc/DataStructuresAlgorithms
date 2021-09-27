/**
 * Linked List Type
 * linkedList.hpp
 * Emiliano Cabrera A01025453  , Do Hyun Nam A01025276
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
        int size;
    
    public:
        LinkedList();

        bool isEmpty() { return size == 0; }; // Checks if linked list is empty
        int getSize() { return size; };

        void addFirst(T data);
        void addLast(T data);
        
        void insertAt(int i, T data);

        T getData(int i);
        void print();

        bool deleteData(T data);
        bool deleteAt(int data);
                
        bool updateAt(int i, T data);
        bool updateData(T prevData, T newData);

        // Methods for homework
        int count(T searchValue);
        void clear();
        void sortedInsert(Node<T> * newNode);
        void removeDuplicates();
        void reverse();
};

template<class T>
LinkedList<T>::LinkedList(){
    this-> head = NULL;
    this-> size = 0;
}

/*
Adds node and heads it, also receives data
Complexity of O(1)

Return void
*/
template<class T>
void LinkedList<T>::addFirst(T data){
    head = new Node<T>(data, head);
    size++; // Increments size count
}

/*
Adds data as last element from a list
Complexity of O(n)

Return void
*/
template<class T>
void LinkedList<T>::addLast(T data){
    if (isEmpty()) {
        head = new Node<T>(data);

    } else { 
        Node<T> *aux = head;

        while (aux -> next != NULL){
            aux = aux -> next;
        }
        aux -> next = new Node<T>(data);
    }
    size++;
}


/* 
Inserts data at a given index 
Time complexity of O(n)

Return void
*/
template<class T>
void LinkedList<T>::insertAt(int i, T data){
    if (!isEmpty() && i >= 1 && i <= size) {
        if (i == 1) {
            addFirst(data);
        } else {
            int counter = 1;
            Node<T> *aux = head;
            Node<T> *previous = head;

            while (aux != NULL){
                if (counter == i) {
                    previous -> next = new Node<T>(data, aux);
                    size++;
                }

                previous = aux;
                aux = aux -> next;                
                counter++;
            }
        }
    } else {
        throw std::runtime_error("OUT OF RANGE\n");
    }
}

/*
Gets the data in the given index position
Time complexity of O(n)

Returns data of any type
*/
template<class T>
T LinkedList<T>::getData(int i){
    if (!isEmpty() && i > 0 && i <= size) {
        // Iterates until node is found, if not it errors out

        int counter = 1;
        Node<T> *aux = head;

        while (counter <= size) {
            if (counter == i) {
                return aux -> data;
            }

            counter++;
            aux = aux->next;
        }
    }

    throw std::runtime_error("OUT OF RANGE\n");
}

/*
Prints list
Time complexity of O(n)

Return void
*/
template<class T>
void LinkedList<T>::print(){
    Node<T> *aux = head;

    if (size > 0) {
        for (int i = 0; i < size; i++) {
            std::cout << aux -> data << " ";
            aux = aux -> next;
        }

    } else {
        std::cout << "LIST IS EMPTY";
    }
    std::cout << "\n";
}

/*
Deletes the given date in its node
Time complexity of O(n)

Returns success of operation as a boolean
*/
template<class T>
bool LinkedList<T>::deleteData(T data){
    if (!isEmpty()) {//mientras que no este vacio
        Node<T> *aux = head;

        if (aux -> data == data){//va buscando hasta encontrar el mismo data
            head = aux -> next;//cambia el next y reduce de size
            size--;
            std::cout << "DELETED" << std::endl;

            return true;
        }

        Node<T> *aux2 = head;
        int count = 0;

        while (count < size) { //itera hasta encontrarlo y hace que el aux sea el next para mover los elementos hasta encontrar el data
            if(aux -> data == data){
                aux2 -> next = aux -> next;
                delete aux;

                size--;
                std::cout << "DELETED" << std::endl;

                return true;
            }

            count++;
            aux2 = aux;
            aux = aux -> next;
        }
    }
    std::cout << "NODE NOT FOUND" << std::endl;

    return false;
}

/*
Deletes the data at a given node
Time complexity of O(n)

Returns success of operation as a boolean
*/
template<class T>
bool LinkedList<T>::deleteAt(int i) {
    if (!isEmpty() && i <= size && i > 0){
        int count = 1;
        Node<T> *aux = head;

        if (i == count) {
            head = aux -> next;
            size--;
            std::cout << "DELETED" << std::endl;

            return true;
        }

        Node<T> *aux2 = head;

        while (count <= size) {
            std::cout << count << " ";

            if (count == i) {
                aux2 -> next = aux -> next;
                delete aux;

                size--;
                std::cout << "DELETED" << std::endl;

                return true;
            }
            count++;
            aux2 = aux;
            aux = aux -> next;
        }
    }
    std::cout << "NODE NOT FOUND" << std::endl;

    return false;
}

/*
Updates data at given node i
Complexity of O(n)

Returns if update was true or false
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
    throw std::runtime_error("OUT OF RANGE");
}

/*
Updates previous data with new data
Time complexity of O(n)

Returns if update was true or false
*/
template<class T>
bool LinkedList<T>::updateData(T prevData, T newData) {
    if (!isEmpty()) {
        Node<T> *aux = head;
        int count = 1;

        while (count <= size) {
            if (aux -> data == prevData){
                aux -> data = newData;
                std::cout << "UPDATED" << std::endl;

                return true;
            }
            count++;
            aux = aux -> next;
        }
    }
    throw std::runtime_error("NOT FOUND\n");
}

/*
Given an element to seach for, it counts the number of times the element appears on the linked list
Time complexity of O(n)

Return an int with number of repetitions
*/
template<class T>
int LinkedList<T>::count(T searchFor){
    int counter = 0; 
    Node<T> *aux = head;  

    while (aux != NULL){
        if (aux -> data == searchFor){
            counter++; 
        }
        aux = aux -> next; 
    }

    std::cout << "The value " << searchFor << " appears " << counter << " times in the list." << std::endl; 

    return counter; 
}; 


/*
Deletes the linked list's nodes completely. Resets the list with NULL head
Time complexity of O(n)

Return void
*/
template<class T>
void LinkedList<T>::clear(){
    while(size>0){
        deleteAt(size);
        size--;
    }
    std::cout << "CLEARED" << std::endl;
}

/* v1.0 (Ascending Order)
Given the linked list with increasing order and a node, it inserts the node at the correct position.
Time complexity of O(n)

Return void

template<class T>
void LinkedList<T>::sortedInsert(Node<T> * newNode){ 
    T addValue = newNode -> data; 
    int index = 1; 
    Node<T> *aux = head;     

    while (aux != NULL && aux -> data > addValue){
        aux = aux -> next; 
        index++; 
    } 

    insertAt(index, addValue);
    if (index == size) {
        addLast(addValue); 
    }

    std::cout << "Node was inserted" << std::endl; 
}; 
*/

/* v2.0 (Descending Order)
Given the linked list with increasing order and a node, it inserts the node at the correct position.
Time complexity of O(n)

Return void
*/
template<class T>
void LinkedList<T>::sortedInsert(Node<T> * newNode){ 
    T addValue = newNode -> data; 
    int index = 1; 
    Node<T> *aux = head;     

    while (aux != NULL && aux -> data > addValue){
        aux = aux -> next; 
        index++; 
    } 

    insertAt(index, addValue);
    if (index == size) {
        addLast(addValue); 
    }

    std::cout << "Node was inserted" << std::endl; 
}; 

/*
Removes all the duplicate data over the list
If list is empty throws error
Time complexity of O(n^2)

Return void
*/
template<class T>
void LinkedList<T>::removeDuplicates(){
    if (!isEmpty()) {
        Node<T> *aux = head;
        std::vector<T> temp;

        while (aux!=NULL) {
            bool continues = true;
            for (T i : temp) {//iterates over data in list
                if(aux -> data == i){
                    continues = false;
                }
            }
            if (continues) {
                temp.push_back(aux -> data);
            } else {
                deleteData(aux -> data);
            }
            aux = aux -> next;
        }
        std::cout << "DUPLICATES DELETED" << std::endl;
        
    }
    else {
      throw std::runtime_error("EMPTY LIST\n");
    }
}

/*
Reverse list storing values over temporal vector
Time complexity of O(n^2)

Return void
*/
template<class T>
void LinkedList<T>::reverse(){
    if (!isEmpty()) {
        std::vector<T> temp; // Temporal vector to store the values
        Node<T> *aux = head;

        while(aux != NULL){
            temp.push_back(aux -> data);
            aux = aux -> next;
        }
        clear(); // Clears list
        for(T i : temp) {
            // Repopulates list in inverse order
            addFirst(i);
        }
    } else{
        throw std::runtime_error("EMPTY LIST\n");
    }
}

#endif
