/**
 * Node type
 * node.hpp
 * Emiliano Cabrera A010  , Do Hyun Nam A01025276
 * 
 */
#ifndef node_hpp
#define node_hpp

template<class T>
struct Node {
    T data; // Contains a data and a pointes as index to next node
    Node<T> *next;
    Node(T data);
    Node(T data, Node<T> *next);
};

//constructor for only data
template <class T>
Node<T>::Node(T data){
    this -> data = data;
    next = NULL;
}

//constructor data and next 
template <class T>
Node<T>::Node(T data, Node<T> *next){
    this -> data = data;
    this -> next = next;
}

#endif