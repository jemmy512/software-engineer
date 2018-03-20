#include<iostream>

using namespace std;

enum Color {RED, BLACK};

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;
    Node(int data) {
        this->data = data;
        left = right = parent = NULL;
    }
};

class RBTree {
private:
    Node *root;
protected:
    void rRotate(Node *&, Node *&);
    void lRotate(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
public:
    RBTree() { root = NULL; }
    void insert(const int &n);
};

Node *BSTInsert(Node *root, Node *node) {
    if (!root)
        return node;
    if (node->data < root->left) {
        root->left = BSTInsert(root->left, node);
        root->left->parent = root;
    } else if (node->data > root->right){
        root->right = BSTInsert(root->right, node);
        root->right->parent = root;
    }
    return root;
}

void RBTree::lRotate(Node *&root, Node *&node) {
    Node *tmp = node->right;
    node->right = tmp->left;
    
    if (node->right != NULL)
        node->right->parent = node;
    if (root == node)
        root = tmp;
    else if (node == node-parent->left)
        node->parent->left = tmp;
    else 
        node->patent->right = tmp;
    tmp->left = node;
    tmp->parent = node->parent;
    node->parent = tmp;
}

void RBTree::rRotate(Node *&root, Node *&node) {
    Node *tmp = node->left;
    node->left = tmp->right;
    
    if (node->left != NULL)
        node->left->parent = node;
    if (node == root)
        root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else 
        node->parent->right = tmp;
    tmp->parent = node->parent;
    node->parent = tmp;
    tmp->right = node;
}

void RBTree::insert(const int &key) {
    Node *node = new Node(key);
    root = BSTInsert(node);
    fixViolation(root, node);
}