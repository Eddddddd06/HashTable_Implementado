#ifndef BST_H
#define BST_H

#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    void insertarRecursivo(Node*& actual, int a) {
        if (actual == nullptr) {
            actual = new Node(a);
            return;
        }

        if (a < actual->value) {
            insertarRecursivo(actual->left, a);
        } else if (a > actual->value) {
            insertarRecursivo(actual->right, a);
        }
    }

    void printPreorderRecursivo(Node* actual) {
        if (actual != nullptr) {
            std::cout << actual->value << " ";
            printPreorderRecursivo(actual->left);
            printPreorderRecursivo(actual->right);
        }
    }

    void printInorderRecursivo(Node* actual) {
        if (actual != nullptr) {
            printInorderRecursivo(actual->left);
            std::cout << actual->value << " ";
            printInorderRecursivo(actual->right);
        }
    }

    void printPostorderRecursivo(Node* actual) {
        if (actual != nullptr) {
            printPostorderRecursivo(actual->left);
            printPostorderRecursivo(actual->right);
            std::cout << actual->value << " ";
        }
    }

    void destruirRecursivo(Node* actual) {
        if (actual != nullptr) {
            destruirRecursivo(actual->left);
            destruirRecursivo(actual->right);
            delete actual;
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destruirRecursivo(root);
    }

    void insertar(int b) {
        insertarRecursivo(root, b);
    }

    void printPreorder() {
        printPreorderRecursivo(root);
        std::cout << std::endl;
    }

    void printInorder() {
        printInorderRecursivo(root);
        std::cout << std::endl;
    }

    void printPostorder() {
        printPostorderRecursivo(root);
        std::cout << std::endl;
    }
};

#endif