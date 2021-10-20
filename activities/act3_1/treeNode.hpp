#ifndef treeNode_hpp
#define treeNode_hpp
#include <iostream>

template<class T>
struct TreeNode{
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode(T data);
    TreeNode(T data, TreeNode<T> *left, TreeNode<T> *right);
};

template <class T>
TreeNode<T>::TreeNode(T data){
    this->data = data;
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T data, TreeNode<T> *left, TreeNode<T> *right){
    this -> data = data;
    this -> left = left;
    this -> right = right;
}

#endif