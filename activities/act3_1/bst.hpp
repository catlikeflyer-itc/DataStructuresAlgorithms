#ifndef bst_hpp
#define bst_hpp
#include <iostream>
#include "treeNode.hpp"
#include "queue.hpp"
#include "stack.hpp"

using namespace std;

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
*/
template<class T>
int BinarySearchTree<T>::countChildren(TreeNode<T>* aux){
	int count = 0; // Counter variable for the children
	aux -> left != NULL ? count ++:count = count; // Add to counter if found on the left
	aux -> right != NULL ? count ++:count = count; // Adds to counter if found on the right
	return count; 
}

//find
//Funcion para verificar si el dato se encuentra en el binary tree
//itera en el arbol y regresa un valor booleano
//O(N)
template<class T>
bool BinarySearchTree<T>::find(T data){
	TreeNode<T> *aux = root;
	bool found = false;
	while (!found && aux!=NULL){
		if(data== aux->data){
			found = true;
		}else{
			data<aux->data?aux=aux->left:aux=aux->right;
		}
	}
	return found;
	
}

//insert
//funcion para insertar en el arbol el valor dado
//hace add al valor al checar en que rama debe de ir y de que nodo
//debe de ser hijo
//O(N)
template<class T>
void BinarySearchTree<T>::insert(T data){
    if(!isEmpty()){
        TreeNode<T> *aux = root;
        while(aux != NULL){
            if(aux->data > data){
                if(aux->left == NULL){
                    aux->left = new TreeNode<T>(data);
                    return;
                } else{
                    aux = aux->left;
                }
            } else{
                if(aux->right == NULL){
                    aux->right = new TreeNode<T>(data);
                    return;
                } else{
                    aux = aux->right;
                }
            }
        }
    } else{
        root = new TreeNode<T>(data);
    }
}


//delete
//Toma un dato de entrada y lo elimina del nodo
//checa que este presente y que no este vacia
// una vez realizado esto mueve los nodos dependiendo del valor
//convirtiendo algun nodo en padre de otros
//O(N2)
template<class T>
void BinarySearchTree<T>::deletes(T data){
	if(isEmpty() ){
		throw runtime_error("Binary tree is empty\n");
	}
	TreeNode<T> *father = root;
	TreeNode<T> *aux = father;
	bool found = false;
	while (!found && aux!=NULL){
		if(data== aux->data){
			found = true;
		}else{
			father = aux;
			data < aux->data?aux = aux->left : aux = aux->right;
		}
	}
	if(found){
		switch (countChildren(aux)){
			case 0:
				if(aux == root){
					delete aux;
					root = NULL;
				}
				else{
					cout<<father->data<<endl;
					data< father -> data ? father -> left = NULL: father->right = NULL;
					delete aux;
				}
				break;
			case 1: //un hijo
				if(aux == NULL){
					root ->left != NULL ? root = root -> left : root = root ->right;
				}
				else{
					if(data<father->data){
						aux->left != NULL ? father -> left = aux->left : father->left = aux->right;
					}else{
						aux->left != NULL ? father -> right = aux->left : father->right = aux->right;
					}
				}
				delete aux;
				break;
			case 2://dos hijos
				TreeNode<T> *father = aux;
				TreeNode<T> *max = aux->left;
				if(max->right ==NULL){
					aux->data = max->data;
					father->left = max ->left;
					delete max;
				}
				else{
					bool found = false;
					while (!found){
						if (max->right==NULL){
							found = true;
						}else{
							father = max;
							max = max ->right;
						}
					}
					aux -> data = max ->data;
					father -> right = max->left;
					delete max;
				}
				break;
		}
	}
	else{
		cout<<"EL VALOR NO ESTA EN EL ARBOL!"<<endl;
	}
}

//printTree
//Funcion para imprimir el arbol
//lo hace de manera horizontal, toma el nodo y el nivel
//O(N)
template<class T>
void BinarySearchTree<T>::printTree(TreeNode<T> *TreeNode, int level){
    if(TreeNode != NULL){
        printTree(TreeNode->right, level + 1);
        for(int i = 0; i < level; i ++){
            cout << " ";
        }
        cout << TreeNode->data << "\n";
        printTree(TreeNode->left, level + 1);
    }
}

//print
//Funcion para imprimir el arbol de manera completa
//lo hace de manera horizontal
//O(N)s
template<class T>
void BinarySearchTree<T>::print(){
	if(!isEmpty()){
		int level = 0;
		cout << endl;
		printTree(root,level);
		cout<<endl;
	}
	else{
		cout<<endl<<"Tree is empty"<<endl<<endl;
	}
}

//Avanzado-----------------------------------------

//preorder
//despliega los datos del nodo en modo
/*
1. Visita la raíz.
2. Atraviesa el subárbol izquierdo, es decir, llama a Preorder (subárbol izquierdo)
3. Atraviesa el subárbol derecho, es decir, llama a Preorder (subárbol derecho)
*/
//O(N)
template<class T>
void BinarySearchTree<T>::preOrder(TreeNode<T> *aux){
	if(aux!=NULL){
		cout<<aux->data<<" ";
		preOrder(aux->left);
		preOrder(aux->right);
	}
}

//inOrder
//despliega los datos del nodo
/*
1. Atraviesa el subárbol izquierdo, es decir, llama a Inorder (subárbol izquierdo)
2. Visite la raíz.
3. Atraviesa el subárbol derecho, es decir, llama a Inorder (subárbol derecho)
*/
//O(N)
template <class T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* aux){
	if(aux!=NULL){
		inOrder(aux->left);
		cout<<aux->data<<" ";
		inOrder(aux->right);
	}
}

//postOrder
//despliega los datos del nodo
/*
1. Atraviesa el subárbol izquierdo, es decir, llama a Postorder (subárbol izquierdo)
2. Atraviesa el subárbol derecho, es decir, llama a Postorder (subárbol derecho)
3. Visite la raíz.
*/
//O(N)
template <class T>
void BinarySearchTree<T>::postOrder(TreeNode<T>* aux){
	if(aux!=NULL){
		postOrder(aux->left);
		postOrder(aux->right);
		cout<<aux->data<<" ";
	}
}

//level by level
//despliega los datos del nodo por nivel
//O(n^2)
template <class T>
void BinarySearchTree<T>::levelByLevel(){
	if(!isEmpty()){
		Queue<TreeNode<T>*> queue;
		queue.enqueue(root);
		while (!queue.isEmpty()){
			TreeNode<T> *aux = queue.dequeue();
			cout<<aux->data<<" ";
			if(aux->left !=NULL){
				queue.enqueue(aux->left);
			}
			if(aux->right !=NULL){
				queue.enqueue(aux->right);
			}
		}
		
	}
}

//height
//itera de manera recursiva sobre el arbol
//O(log n)
template <class T>
int BinarySearchTree<T>::height(TreeNode<T> *TreeNode){
	int h = 0;
	int l,r;
	if(TreeNode != NULL){
		h++;
		l = height(TreeNode->left);
		r = height(TreeNode->right);
		(l>r)? h+=l:h+=r;
	}
	return h;

}

//getHeight
//usado para llavar a la funcion recursiva
//O(1)
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
						cout<<data<<" ";
					}catch(runtime_error& e){
						cout<<e.what()<<endl;
					}
				}
				
			}else {
				cout<<"No tiene ancestros"<<endl;
			}
		}
	}else{
		cout<<"EL ARBOL ESTA VACIO"<<endl;
	}
}

//whatLevelAmI
//funcion para obtener el nivel donde te encuentras en un dato
//O(N)
template <class T>
int BinarySearchTree<T>::whatLevelAmI(T data){
	if(!isEmpty()){
		TreeNode<T> *aux = root;
		int count = 0;
		while (aux != NULL){
			if(aux->data == data){
                return count;
            }
            count++;
            aux->data > data ? aux = aux->left : aux = aux->right;
		}	
	}
	throw runtime_error("Binary tree is empty\n");
}

//visit
//funcion para llamar a los metodos de recorrido
//O(1)
template <class T>
void BinarySearchTree<T>::visit(int selection){
	if(!isEmpty()){
		switch (selection){
			case 1:
				cout << "Preorder: ";
            	preOrder(root);
				break;
			case 2:
				cout << "Inorder: ";
				inOrder(root);
				break;
			case 3:
				cout << "Postorder: ";
				postOrder(root);
				break;
			case 4:
				cout << "Level by level: ";
				levelByLevel();
				break;
			default:
				cout <<"Seleccion invalida"<<endl;
				break;
		}
	}
}

#endif