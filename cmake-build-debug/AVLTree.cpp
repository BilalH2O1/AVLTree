//
// Created by Bilal Abdulwahab on 2026-04-05.
//

#include "AVLTree.h"
#include <algorithm>

template<typename E>
AVLTree<E>::AVLTree() : root(nullptr), number_of_node(0) {
}

template<typename E>
AVLTree<E>::~AVLTree() {
    cleartree(root);
}


template<typename E>
int AVLTree<E>::height(Node *n) const {
    return n == nullptr ? -1 : n->hauteur;
}

template<typename E>
int AVLTree<E>::getBalance(Node *n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
}

template<typename E>
void AVLTree<E>::cleartree(Node *t) {
    if (t != nullptr) {
        cleartree(t->left);
        cleartree(t->right);
        delete t;
    }
}

template<typename E>
typename AVLTree<E>::Node *AVLTree<E>::insertRecursive(Node *node, const E &data) {
    //STEP 1: The base case (we found the empty spot)
    if (node == nullptr) {
        return new Node(data);
    }
    //STEP 2: going down
    if (data < node->data) {
        node->left = insertRecursive(node->left, data);
    } else if (data > node->data) {
        node->right = insertRecursive(node->right, data);
    } else {
        return node;
    }

    node->hauteur = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);
    //LL
    if (balance > 1 && data < node->left->data) {
        return rotateRight(node);
    }
    //RR
    if (balance < -1 && data > node->right->data) {
        return rotateLeft(node);
    }
    //LR
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    //RL
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;

}

template<typename E>
typename AVLTree<E>::Node *AVLTree<E>::rotateRight(Node *y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;

    y->hauteur = 1 + std::max(height(y->left), height(y->right));
    x->hauteur = 1 + std::max(height(x->left), height(x->right));
    return x;
}

template<typename E>
typename AVLTree<E>::Node *AVLTree<E>::rotateLeft(Node *x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;

    x->hauteur = 1 + std::max(height(x->left), height(x->right));
    y->hauteur = 1 + std::max(height(y->left), height(y->right));
    return y;
}

template<typename E>
typename AVLTree<E>::Node *AVLTree<E>::rotateLeftRight(Node *z) {
    Node* y = z->left;
    Node* x = y->right;

    z->left = rotateLeft(y);
    return rotateRight(z);

}

template<typename E>
typename AVLTree<E>::Node *AVLTree<E>::rotateRightLeft(Node *z) {
    Node* y = z->right;
    Node* x = y->left;

    z->right = rotateRight(y);
    return rotateLeft(z);
}


template<typename E>
void AVLTree<E>::insert(const E &data) {
    insertRecursive(data);
    ++number_of_node;
}

template<typename E>
bool AVLTree<E>::search(const E &data) {
    Node* current = root;
    while (current != nullptr) {
        if (data == current->data) {
            return true;
        } else if (data > current->data) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return false;
}

/*template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::removeRecursive(Node *node, const E &data) {
    if (node == nullptr) return nullptr;
    if (data < node->data) removeRecursive(node->left, data);
    if (data > node->data) removeRecursive(node->right, data);
    else if (node->left != nullptr && node->right != nullptr) {
        Node* temp = node->right;
        Node* parent = node;
        while (parent->left != nullptr) {
            parent = temp;
            temp = temp->left;
        }
        node->data = temp->data;
        if (temp == node->left) {
            removeRecursive(parent->left, temp->data);
        } else {
            removeRecursive(parent->right, temp->data);
        }
    } else {
        Node* oldNode = node;
        node = (node->left != 0) ? node->left : node->right;
        delete node;
        --number_of_node;
    }

}*/

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::removeRecursive(Node *node, const E &data) {
    if (node == nullptr) return nullptr; //that's if the parameter is nullptr
    //now we start searching
    if (data < node->data) node->left = removeRecursive(node->left, data);
    else if (data > node->data) node->right = removeRecursive(node->right, data);
    else {
        //case 1:
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        //case 2.1:
        if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;

        }
        //case 2.2:
        if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        //case 3:
        if (node->left != nullptr && node->right != nullptr) {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->data = temp->data;

            node->right = removeRecursive(node->right, temp->data);


        }
    }

    node->hauteur = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance();

    if (balance > 1 && getBalance(node->left) >= 0) {
        rotateLeft(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) {
        rotateRight(node);
    }
    if (balance > 1 && getBalance(node->right) < 0) {
        node->left = rotateLeft(node->left);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template<typename E>
bool AVLTree<E>::deleteNode(const E &data) {

}













