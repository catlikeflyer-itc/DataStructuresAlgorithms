#ifndef bst_hpp
#define bst_hpp
#include <iostream>
#include "treeNode.hpp"
#include "queue.hpp"
#include "stack.hpp"

// Binary Search Tree Class
template <class T>
class BinarySearchTree {
    private:
        TreeNode<T> *root; 

    public:
        BinarySearchTree();

        bool find(T data); 
        bool isEmpty(){return root == NULL;};

        void insert(T data);
        void deletes(T data);

        void preOrder(TreeNode<T> *aux);
        void inOrder(TreeNode<T> *aux);
        void postOrder(TreeNode<T>* aux);
        void levelByLevel();
        void visit(int selection);


        int height(TreeNode<T>* TreeNode);
        int getHeight();
        void ancestors(T data);
        int whatLevelAmI(T data);

        int countChildren(TreeNode<T>* aux);
        void printTree(TreeNode<T> *TreeNode, int level);
        void print();
};

// Constructor
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	root = NULL; // Inits TreeNode as NULL
}

/*
Counts the number of children from the tree, iterates from left to right branches
Returns an integer
O(n)
*/
template<class T>
int BinarySearchTree<T>::countChildren(TreeNode<T>* aux){
	int count = 0; // Counter variable for the children
	aux -> left != NULL ? count ++:count = count; // Add to counter if found on the left
	aux -> right != NULL ? count ++:count = count; // Adds to counter if found on the right
	return count; 
}

/*
Iterates to find a given value through the tree
Returns a boolean if value is found

O(n)
*/
template<class T>
bool BinarySearchTree<T>::find(T data){
	TreeNode<T> *aux = root;
	bool found = false;

	while (!found && aux!=NULL) {
		if (data == aux -> data){
			found = true;
		} else {
			data < aux -> data ? aux = aux -> left : aux = aux -> right;
		}
	}

	return found;
	
}

/*
Inserts a given value to the tree, checks the most fitting branch and node, it has to be a child
Returns void

O(n)
*/
template<class T>
void BinarySearchTree<T>::insert(T data){
    if (!isEmpty()) {
        TreeNode<T> *aux = root;

        while (aux != NULL) {
            if (aux -> data > data) {
                if (aux -> left == NULL) {
                    aux -> left = new TreeNode<T>(data);

                    return;
                } else {
                    aux = aux -> left;
                }
            } else {
                if (aux -> right == NULL) {
                    aux -> right = new TreeNode<T>(data);
                    
					return;
                } else {
                    aux = aux -> right;
                }
            }
        }
    } else {
        root = new TreeNode<T>(data);
    }
}

/*
Deletes the given value from the node. First it checks the node is not empty and the value is present. After deletion, 
it moves the nodes accordingly and sets a child as a parent node
Returns void

O(n^2)
*/
template<class T>
void BinarySearchTree<T>::deletes(T data){
	if (isEmpty()) {
		throw std::runtime_error("Binary tree is empty\n");
	}

	TreeNode<T> *father = root;
	TreeNode<T> *aux = father;
	bool found = false;

	while (!found && aux != NULL){
		if (data == aux -> data) {
			found = true;
		} else {
			father = aux;
			data < aux -> data ? aux = aux -> left : aux = aux -> right;
		}
	}
	if (found) {
		switch (countChildren(aux)) {
			case 0:
				if (aux == root) {
					delete aux;
					root = NULL;
				} else {
					std::cout << father -> data << std::endl;
					data < father -> data ? father -> left = NULL: father -> right = NULL;
					delete aux;
				}

				break;

			case 1: // One child
				if (aux == NULL) {
					root -> left != NULL ? root = root -> left : root = root -> right;
				} else {
					if (data < father -> data) {
						aux -> left != NULL ? father -> left = aux -> left : father -> left = aux -> right;
					} else {
						aux -> left != NULL ? father -> right = aux -> left : father -> right = aux -> right;
					}
				}
				delete aux;

				break;

			case 2: // Two children
				TreeNode<T> *father = aux;
				TreeNode<T> *max = aux -> left;

				if (max -> right == NULL) {
					aux -> data = max -> data;
					father -> left = max -> left;
					delete max;
				} else {
					bool found = false;

					while (!found) {
						if (max -> right == NULL) {
							found = true;
						} else {
							father = max;
							max = max -> right;
						}
					}

					aux -> data = max -> data;
					father -> right = max -> left;
					delete max;
				}

				break;
		}
	} else {
		std::cout << "Value not on tree!" << std::endl;
	}
}

/*
Prints tree horizontally given a level
Returns void

O(n)
*/
template<class T>
void BinarySearchTree<T>::printTree(TreeNode<T> *TreeNode, int level) {
    if (TreeNode != NULL) {
        printTree(TreeNode->right, level + 1);
        for (int i = 0; i < level; i ++) {
            std::cout << " ";
        }
        std::cout << TreeNode -> data << "\n";
        printTree(TreeNode -> left, level + 1);
    }
}

/*
Prints whole tree level by level
Returns void

O(n)n
*/
template<class T>
void BinarySearchTree<T>::print(){
	if(!isEmpty()){
		int level = 0;
		std::cout << std::endl;
		printTree(root,level);
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl << "Tree is empty" << std::endl;
	}
}

/*
Preorder
1. Visits root
2. Calls preorder from the left subtree
3. Calls preorder from the right siubtree

Returns void

O(n)
*/
template<class T>
void BinarySearchTree<T>::preOrder(TreeNode<T> *aux){
	if (aux != NULL) {
		std::cout << aux -> data << " ";
		preOrder(aux -> left);
		preOrder(aux -> right);
	}
}

/*
Inorder
1. Calls inorder from the left subtree
2. Visits root
3. Calls inorder from the right subtree

Returns void

O(n)
*/
template <class T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* aux){
	if (aux != NULL) {
		inOrder(aux -> left);
		std::cout << aux -> data << " ";
		inOrder(aux -> right);
	}
}

/*
Post order
1. Calls post orther from the left subtree
2. Calls postorder from the right subtree
3. Visits root

Returns void

O(n)
*/
template <class T>
void BinarySearchTree<T>::postOrder(TreeNode<T>* aux){
	if (aux != NULL) {
		postOrder(aux -> left);
		postOrder(aux -> right);
		std::cout << aux -> data << " ";
	}
}

/*
Level by level
Shows values in tree by levels
Returns void

O(n^2)
*/
template <class T>
void BinarySearchTree<T>::levelByLevel(){
	if(!isEmpty()){
		Queue<TreeNode<T>*> queue;

		queue.enqueue(root);
		while (!queue.isEmpty()) {
			TreeNode<T> *aux = queue.dequeue();
			std::cout << aux -> data << " ";
			if (aux -> left != NULL) {
				queue.enqueue(aux -> left);
			}
			if (aux -> right != NULL) {
				queue.enqueue(aux -> right);
			}
		}
		
	}
}

/*
Function that displays a menu to choose method to parse the tree

O(n)
*/
template <class T>
void BinarySearchTree<T>::visit(int selection){
	if(!isEmpty()){
		switch (selection){
			case 1:
				std::cout << "Preorder: ";
            	preOrder(root);
				break;
			case 2:
				std::cout << "Inorder: ";
				inOrder(root);
				break;
			case 3:
				std::cout << "Postorder: ";
				postOrder(root);
				break;
			case 4:
				std::cout << "Level by level: ";
				levelByLevel();
				break;
			default:
				std::cout << "Seleccion invalida" << std::endl;
				break;
		}
	}
}

/*
Recursively iterates to tree to measure its height using a counter
Returns integer of height

O(log n)
*/
template <class T>
int BinarySearchTree<T>::height(TreeNode<T> *TreeNode){
	int h = 0;
	int l,r;
	if (TreeNode != NULL){
		h++;
		l = height(TreeNode -> left);
		r = height(TreeNode -> right);
		(l > r) ? h += l : h += r;
	}

	return h;

}


/*
Used to call the above function
Returns height

O(n)
*/
template <class T>
int BinarySearchTree<T>::getHeight(){
	TreeNode<T>  *aux = root;
	int h = height(root);

	return h;
}

//ancestors
//funcion para obtener los ancestros de un dato
//O(N)
template <class T>
void BinarySearchTree<T>::ancestors(T data){
	if(!isEmpty()){
		TreeNode<T>  *aux = root;
		Stack<T> stack;
		if(aux->data !=data){
			bool notFound = false;
			while (aux->data != data && !notFound){
				stack.push(aux->data);
				if(data<-aux->data){
					if(aux->left == NULL){
						notFound = true;
					}else{
						aux = aux->left;
					}
				}else{
					if(aux->right == NULL){
						notFound = true;
					}else{
						aux = aux->right;
					}
				}
			}
			if(!notFound){
				while (!stack.isEmpty()){
					try{
						T data = stack.pop();
						std::cout << data <<" ";
					} catch (std::runtime_error & e) {
						std::cout << e.what() << std::endl;
					}
				}
				
			} else {
				std::cout << "No tiene ancestros" << std::endl;
			}
		}
	} else {
		std::cout << "EL ARBOL ESTA VACIO" << std::endl;
	}
}

/*
Finds out what level a data is located at
Returns int of level

O(n)
*/
template <class T>
int BinarySearchTree<T>::whatLevelAmI(T data){
	if (!isEmpty()) {
		TreeNode<T> *aux = root;
		int count = 0;
		while (aux != NULL) {
			if (aux -> data == data) {
                return count;
            }
            count++;
            aux -> data > data ? aux = aux -> left : aux = aux -> right;
		}	
	}
	throw std::runtime_error("Binary tree is empty!\n");
}

#endif