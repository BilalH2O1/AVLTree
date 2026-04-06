
#ifndef AVLTREE_H
#define AVLTREE_H
template <typename E>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(const E& data);
    bool search(const E& data);
    bool deleteNode(const E& data);
private:
    class Node {
    public:
        E data;
        Node* left;
        Node* right;
        int hauteur;
        explicit Node(const E& d) :  data(d), left(nullptr), right(nullptr), hauteur(0) { }
    };

    Node* root; //the root of our tree
    long number_of_node; //number of nodes in our tree

    int height(Node* n) const; //gives the height of a node
    int getBalance(Node* n); //calculate height(left) - height(right)

    Node* rotateRight(Node* y); //LL
    Node* rotateLeft(Node* x); //RR
    Node* rotateLeftRight(Node* z); //LR
    Node* rotateRightLeft(Node* z); //RL

    Node* insertRecursive(Node* node, const E& data); //helper function for insertion
    Node* removeRecursive(Node* node, const E& data);
    void cleartree(Node* t);
};
#endif //AVLTREE_H
