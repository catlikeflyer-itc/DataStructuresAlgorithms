#ifndef _BINARYSEARCHTREE_H
#define _BINARTSEARCHTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std; 

class BTreeNode{
    private: 
        pair<string, int> value; 
        BTreeNode * left; 
        BTreeNode* right;
        int depth; 

    public: 
        ~BTreeNode() {}; 
        BTreeNode() {}; 
        BTreeNode(string name, int num){
            value.first = name; 
            value.second = num; 
            left = nullptr; 
            right = nullptr; 
        };

        BTreeNode(pair<string,int> val){
            value = val;  
            left = nullptr; 
            right = nullptr; 
        };

        BTreeNode(string name, int num, BTreeNode *_left, BTreeNode *_right ){
            value.first = name; 
            value.second = num;  
            left = _left; 
            right = _right; 
        }; 

         BTreeNode(pair<string,int> val, BTreeNode *_left, BTreeNode *_right ){
            value = val; 
            left = _left; 
            right = _right; 
        }; 

        pair<string, int> getValue(){
            return value; 
        };

        string getValueName(){
            return value.first;
        }

        int getValueNum(){
            return value.second;
        }

        BTreeNode *getLeft(){
            return left; 
        };

        BTreeNode *getRight(){
            return right; 
        };

        void setValue(pair<string, int> val){
            value = val; 
        };

        void setValueName(string name){
            value.first = name; 
        }

        void setValueNum (int num){
            value.second = num; 
        }

        void setLeft(BTreeNode *node){
            left = node; 
        }; 

        void setRight(BTreeNode *node){
            right = node; 
        }; 

        void printInOrder(){
            if(right!=nullptr) right->printInOrder();
            cout << value.first << ":\t" << value.second << endl;
            if(left!=nullptr) left->printInOrder();
        }

        void printInOrderRec(int n, int i){
            if(n == i) return;
            i++;
            cout << "i: " << i << endl; 
            if(right!=nullptr) right->printInOrderRec(n, i);
            cout << value.first << ":\t" << value.second << endl;
            if(left!=nullptr) left->printInOrderRec(n, i);
            
        }

        void printInOrder(int n){
            n--; 
            if(n == 0){
                return; 
            }
            if(right!=nullptr) right->printInOrder(n);
            cout << value.first << ":\t" << value.second << endl;
            if(left!=nullptr) left->printInOrder(n);
        }
}; 

class BinarySearchTree{
    private:
        BTreeNode *root;
        int size = 0;
    public:
        ~BinarySearchTree(){};
        BinarySearchTree(){
            root = nullptr;
            size++;
        }
        
        int getSize(){
            return size;
        }
        
        bool insertNode(string name, int num){
            BTreeNode *ptr = root;
            BTreeNode* pre = nullptr;
            // Ver si existe
            while(ptr != nullptr){
                // SI el nombre existe, no insertar nada
                if (ptr->getValueName() == name)
                    return false;
                pre = ptr;
                ptr = ptr->getValueNum() > num ? ptr->getLeft() : ptr->getRight();
            }
            BTreeNode *new_node = new BTreeNode(name, num);

            if (pre == nullptr)
                root = new_node;
            else {
                if (pre->getValueNum() < num)
                    pre->setRight(new_node);
                else
                    pre->setLeft(new_node);            
            }
            size++; 
            return true;
        }

        void printInOrder(){
            root->printInOrder();
        }

        void printInOrder(int n){
            root->printInOrder(n);
        }

        void printLast(){
            BTreeNode *ptr = root;
            while(ptr->getRight()!=nullptr){
                ptr = ptr->getRight();
            }
            cout << ptr->getValueName() << ":\t" << ptr->getValueNum() << endl;
        }


        // Usamos como referencia:  https://www.geeksforgeeks.org/kth-largest-element-in-bst-when-modification-to-bst-is-not-allowed/ 
         
        void kthLargestRec(BTreeNode *root, int n, int &visitedNodes){ 
            if (root == NULL || visitedNodes >= n) return; 
            // Derecho
            kthLargestRec(root->getRight(), n, visitedNodes); 
            visitedNodes++; 
            // Si es el enésimo 
            if (visitedNodes == n) { 
                cout << root->getValueName() << ":\t" << root->getValueNum() << endl;
                return; 
            }
            // Izquierdo 
            kthLargestRec(root->getLeft(), n, visitedNodes); 
        } 
        
        void kthLargest(BTreeNode *root, int n){ 
            int visitedNodes = 0; 
            kthLargestRec(root, n, visitedNodes); 
        } 

        void printKth(int n){
            for(int i = 0; i <= n; i++){
                kthLargest(root, i); 
            }
        }

        void saveKthLargestRec(BTreeNode *root, int n, int &visitedNodes, map<string, int> &mappy){ 
            if (root == NULL || visitedNodes >= n) return; 
            // Derecho
            saveKthLargestRec(root->getRight(), n, visitedNodes, mappy); 
            visitedNodes++; 
            // Si es el enésimo 
            if (visitedNodes == n) { 
                mappy[ root->getValueName() ] += root->getValueNum();
                return; 
            }
            // Izquierdo 
            saveKthLargestRec(root->getLeft(), n, visitedNodes, mappy); 
        } 
        
        void saveKthLargest(BTreeNode *root, int n, map<string, int> &mappy){ 
            int visitedNodes = 0; 
            saveKthLargestRec(root, n, visitedNodes, mappy); 
        } 

        void saveKth(int n, map<string, int> &mappy){
            for (int i = 0; i <= n; i++){
                saveKthLargest(root, i, mappy); 
            }
        }

};

#endif