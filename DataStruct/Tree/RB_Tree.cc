/*
*   Reference: https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
*/

#include<iostream>

using namespace std;

enum Color {RED, BLACK};

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;
    Node(int data) {
        this->data = data;
        // color  = RED;
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
    void inOrder();
    void insert(const int &n);
};

Node *BSTInsert(Node *root, Node *node) {
    if (!root)
        return node;
    if (node->data < root->data) {
        root->left = BSTInsert(root->left, node);
        root->left->parent = root;
    } else if (node->data > root->data){
        root->right = BSTInsert(root->right, node);
        root->right->parent = root;
    }
    return root;
}

void inOrderUtil(Node *root) {
    if (root) {
        inOrderUtil(root->left);
        cout << root->data << " ";
        inOrderUtil(root->right);
    }
}

void RBTree::inOrder() { inOrderUtil(root); }

void RBTree::lRotate(Node *&root, Node *&node) {
    Node *tmp = node->right;
    
    node->right = tmp->left;
    if (node->right != NULL)            // 1. modify node->right
        node->right->parent = node;
    
    if (root == node)                   // 2. modify node->parent
        root = tmp;
    else if (node == node->parent->left) 
        node->parent->left = tmp;
    else 
        node->parent->right = tmp;
    
    tmp->left = node;                   // 3. modify tmp
    tmp->parent = node->parent;
    node->parent = tmp;                 // 4. modify node
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
    tmp->right = node;
    node->parent = tmp;
}

void RBTree::fixViolation(Node *&root, Node *&node) {
    Node *parent, *parent_g, *uncle;
    parent = parent_g = uncle = NULL;
    
    while ((node != root) && (node->color == RED) && (node->parent->color == RED)) {
        parent = node->parent;
        parent_g = parent->parent;
        
// Case A: parent is on the left of the parent_g -------------------------------
        if (parent == parent_g->left) {
            uncle = parent_g->right;
            if (uncle && RED == uncle->color) { // Case 1. uncle color is red
                parent->color = uncle->color = BLACK;
                parent_g->color = RED;
                node = parent_g;
            } else {
                if (node == parent->right) {    // Case 2. left right
                    lRotate(root, parent);
                    node = parent; 
                    parent = node->parent;
                }
                rRotate(root, parent_g);        // Case 3. left left
                swap(parent->color, parent_g->color);
                node = parent;
            }
// Case B: parent is on the right of the parent_g ------------------------------
        } else { 
            uncle = parent_g->left;
            if (uncle && RED == uncle->color) { // Case 1. uncle is red
                parent->color = uncle->color = BLACK;
                parent_g->color = RED;
                node = parent_g;
            } else {
                if (parent == parent_g->left) { // case 2. right left
                    rRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                lRotate(root, parent_g);        // case 3. right right
                swap(parent->color, parent_g->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

void RBTree::insert(const int &key) {
    Node *node = new Node(key);
    root = BSTInsert(root, node);
    fixViolation(root, node);
}

int main(void) {
    RBTree tree;
 
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);  
    
    cout << "Inorder traversal of RBTree:\n";
    tree.inOrder();
    
    return 0;
}