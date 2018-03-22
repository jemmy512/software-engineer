/*
*   Reference: https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
*   https://juejin.im/entry/58371f13a22b9d006882902d#%E7%BA%A2%E9%BB%91%E6%A0%91%E7%9A%84%E5
        %B9%B3%E8%A1%A1%E5%88%A0%E9%99%A4
        http://www.cnblogs.com/skywang12345/p/3245399.html#a1
*/

#include<iostream>

using namespace std;

enum Color {RED, BLACK, BBLACK};

struct Node {
    int data;
    int color;
    Node *left, *right, *parent;
    Node(int data) {
        this->data = data;
        color  = RED;
        left = right = parent = NULL;
    }
};

class RBTree {
private:
    Node *root;
protected:
    void BSTDelete(Node *&, int);
    void BSTInsert(Node *&, Node *&);
    void rRotate(Node *&, Node *&);
    void lRotate(Node *&, Node *&);
    void fixDeletion(Node *&, Node *&);
    void fixInsertion(Node *&, Node *&);
public:
    RBTree() { root = NULL; }
    void inOrder(Node *);
    void RBInsert(const int &n);
    void RBDelete(int key);
    void getColor(Node *&node) {
        if (node == NULL)
            return BLACK;
        return node->color;
    }
    void setColor(Node *&node, int color) {
        if (!node)
            return;
        node->color = color;
    }
};

Node *minNode(Node *root) {
    while(root->left)
        root = root->left;
    return root;
}

void inOrderUtil(Node *root) {
    if (root) {
        inOrderUtil(root->left);
        cout << root->data << " ";
        inOrderUtil(root->right);
    }
}

void RBTree::inOrder(Node *&root) { inOrderUtil(root); }

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
    
    node->left = tmp->right;            // 1. modify node->left
    if (node->left != NULL)
        node->left->parent = node;
    
    if (node == root)                   // 2. modify node->parent
        root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else 
        node->parent->right = tmp;
    
    tmp->parent = node->parent;         // 3. modify tmp
    tmp->right = node;
    node->parent = tmp;                 // 4. modify node
}

Node *RBTree::BSTInsert(Node *&root, Node *&node) {
    if (!root)
        return node;
    if (node->data < root->data) {      // 1. left insert
        root->left = BSTInsert(root->left, node);
        root->left->parent = root;
    } else if (node->data > root->data){// 2. right inset
        root->right = BSTInsert(root->right, node);
        root->right->parent = root;
    }
    return root;                        // 3. no insert
}

Node *RBTree::BSTDelete(Node *&root, int key) {
    if (!root)
        return root;
    if (key == root->data) {
        if (root->left && root->right)  // 1. has two children
            root->data = minNode(root->right)->data;
            return BSTDelete(root->right, root->data);
        } else {                        // 2. has one or zero child
            return root;
        }
    } else if (key < root->data){
        return BSTDelete(root->left, key);
    } else {
        return BSTDelete(root->right, key);
    }
}

void RBTree::fixInsertion(Node *&root, Node *&node) {
    Node *parent, *parent_g, *uncle;
    parent = parent_g = uncle = NULL;
    
    while ((node != root) && (getColor(node) == RED) && (getColor(node->parent) == RED)) {
        parent = node->parent;
        parent_g = parent->parent;
        
// Case A: parent is on the left of the parent_g -------------------------------
        if (parent == parent_g->left) {
            uncle = parent_g->right;
            if (uncle && RED == getColor(uncle)) { // Case 1. uncle color is red
                setColor(parent) = setColor(uncle) = BLACK;
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

void RBTree::fixDeletion(Node *&root, Node *node) {
    if (root == NULL)
        return;
    if (node == root) {
        root = NULL;
        return;
    }
// Case A: one child or node is red
    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left ? node->left : node->right;
        if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        if (child)
            child->parent = node->parent;
        setColor(child, BLACK);
        delete(node);
// Case B: The color of child of node and node are all black
    } else {
        Node *parent = node->parent;
        Node *sibling = NULL;
        Node *pt = node;
        setColor(pt, BBLACK);
        while (pt != root && getColor(pt) == BBLACK) {
            if (node == parent->left) {
                 sibling = parent->right;
                 if (getColor(sibling) == RED) {   // Case 1. sibling is red
                     setColor(sibling, BLACK);
                     setColor(parent, RED);
                     lRotate(parent);
                 } else {
                                                // Case 2. sibling children are all black
                     if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                         setColor(sibling, RED);
                         if (getColor(parent) == RED)
                             setColor(parent, BLACK);
                         else 
                             setColor(parent, BBLACK);
                         pt = parent;
                     } else {                   // Case 3. sibling right child is black
                         if (getColor(sibling->right) == BLACK) {
                             setColor(sibling->left, BLACK);
                             setColor(sibling, RED);
                             rRotate(sibling);
                             sibling = parent->right;
                         }
                         // Case 4. sibling righg child red
                         setColor(sibling, parent->color);
                         setColor(parent, BLACK);
                         setColor(sibling->right, BLACK);
                         lRotate(parent);
                         break;
                     }
                 }
            } else {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            
                        }
                    }
                }
            }            
        }
        if (node == parent->left);
            parent->left = NULL;
        else 
            parent->right = NULL;
        delete(node);
        setColor(root, BLACK);
    }
}

void RBTree::RBInsert(const int &key) {
    Node *node = new Node(key);
    root = BSTInsert(root, node);
    fixInsertion(root, node);
}

void RBTree::RBDelete(Node *&root, int key) {
    Node *node = BSTDelete(root, key);
    fixDeletion(root, node);
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