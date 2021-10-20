#ifndef node_hpp
#define node_hpp
#include<iostream>

template<class T>
struct Node{
    T data;
    Node<T> *left;
    Node<T> *right;
    Node(T data);
    Node(T data, Node<T> *left, Node<T> *right);
};

template <class T>
Node<T>::Node(T data){
    this -> data = data;
    left = NULL;
    right = NULL;
}

template <class T>
Node<T>::Node(T data, Node<T> *left, Node<T> *right){
    this -> data = data;
    this -> left = left;
    this -> right = right;
}

#endif