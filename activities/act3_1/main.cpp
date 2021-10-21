#include <iostream>
#include "bst.hpp"

using namespace std;

/*
Displays menu to test the BST
Return void
*/
void menu() {
    std::cout << "\n-----------Basics------------" << std::endl;
    std::cout << std::endl;
    std::cout << "1) Insert" << std::endl;
    std::cout << "2) Delete" << std::endl;
    std::cout << "3) Find" << std::endl;
    std::cout << "4) Print" << std::endl;
    std::cout << "-----------Activity 3.3------------" << std::endl;
    std::cout << "5) Visit" << std::endl;
    std::cout << "6) Height" << std::endl;
    std::cout << "7) Ancestors" << std::endl;
    std::cout << "8) What level am I" << std::endl;
    std::cout << "9) Exit" << std::endl;
    std::cout << "\n" << std::endl;
}

/*
Initializes a tree with the given values 
Return void
*/
void initTree(BinarySearchTree<int> &tree){
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(3);
    tree.insert(8);
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(28);
}

int main() {
    BinarySearchTree<int> tree;
    initTree(tree);
	bool continues = true;
    int selection, value, selection2;
    bool found;

    std::cout << "BST tester: " << endl;
    while (continues) {
        menu();
        std::cout << "Ingresa una opcion del menu: "; std::cin >> selection;

        // Switch to call user function accordingly
        switch (selection) {
            case 1:
                std::cout << std::endl << "Ingresa el valor a insertar: "; std::cin >> value;
                tree.insert(value);

                break;

            case 2:
                std::cout << std::endl << "Ingresar el valor a borrar: "; std::cin >> value;
                tree.deletes(value);

                break;

            case 3:
                std::cout << std::endl << "Ingresar el valor a buscar: "; std::cin >> value;
                found = tree.find(value);

                if (found) {
                    std::cout << std::endl << "El valor se encuentra en el arbol!" << std::endl;
                } else {
                    std::cout << std::endl << "El valor no esta en el arbol" << std::endl;
                }

                break;

            case 4:
                tree.print();

                break;

            case 5:
                std::cout << std::endl << "1) Preorder" << std::endl;
                std::cout << "2) Inorder" << std::endl;
                std::cout << "3) Postorder" << std::endl;
                std::cout << "4) Level by level\n" << std::endl;
                std::cout << std::endl << "Ingresa una opcion de visita: "; std::cin >> selection2;
                tree.visit(selection2);

                break;
            
            case 6:
                std::cout << "Altura del arbol: " << tree.getHeight() << std::endl;

                break;

            case 7:
                std::cout << std::endl << "Ingresar el valor a buscar sus ancestros: "; std::cin >> value;
                tree.ancestors(value);

                break;

            case 8:
                std::cout << std::endl << "Ingresar el valor a encontrar su nivel: "; std::cin >> value;
                std::cout << "El nivel en el que esta " << value << ": " << tree.whatLevelAmI(value);

                break;

            case 9:
                continues = false;

                break;

            default:
                std::cout << "------------------------------------"<< std::endl;
                std::cout << std::endl << "Valor invalido!" << std::endl;
                std::cout << "------------------------------------"<< std::endl;

                break;
        }
    }

    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl << std::endl << "Exit program\n" << std::endl;

    return 0;
}