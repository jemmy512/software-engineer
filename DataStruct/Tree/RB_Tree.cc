/*
*   Reference: https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
*   https://juejin.im/entry/58371f13a22b9d006882902d#%E7%BA%A2%E9%BB%91%E6%A0%91%E7%9A%84%E5
*       %B9%B3%E8%A1%A1%E5%88%A0%E9%99%A4
*       http://www.cnblogs.com/skywang12345/p/3245399.html#a1
*       http://blog.csdn.net/weewqrer/article/details/51866488
*/

#include<iostream>
#include<iomanip>
using namespace std;

enum Color {RED, BLACK};

struct Node {
    int data;
    int color;
    Node *left, *right, *parent;
    Node(int data) {
        this->data = data;
        color  = RED;
        left = right = parent = nullptr;
    }
};

class RBTree {
private:
    Node *root;
protected:
    Node *BSTDelete(Node *&, int);
    Node *BSTInsert(Node *&, Node *&);
    void rRotate(Node *&, Node *&);
    void lRotate(Node *&, Node *&);
    void fixDeletion(Node *&, Node *&);
    void fixInsertion(Node *&, Node *&);
public:
    RBTree() { root = nullptr; }
    void inOrder();
    void RBInsert(const int &n);
    void RBDelete(const int key);
    int getColor(Node *&node) {
        if (node == nullptr)
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
        cout << setw(2) << root->data << " c: " << root->color << endl;
        inOrderUtil(root->right);
    }
}

void RBTree::inOrder() { inOrderUtil(root); }

void RBTree::lRotate(Node *&root, Node *&node) {
    Node *tmp = node->right;
    
    node->right = tmp->left;
    if (node->right != nullptr)            // 1. modify node->right
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
    if (node->left != nullptr)
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
        if (root->left && root->right) {// 1. has two children
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
    parent = parent_g = uncle = nullptr;
    
    while ((node != root) && (getColor(node) == RED) && (getColor(node->parent) == RED)) {
        parent = node->parent;
        parent_g = parent->parent;
        
// Case A: parent is on the left of the parent_g -------------------------------
        if (parent == parent_g->left) {
            uncle = parent_g->right;
            if (uncle && RED == getColor(uncle)) { // Case 1. uncle color is red
                setColor(parent, BLACK);
                setColor(uncle, BLACK);
                setColor(parent_g, RED);
                node = parent_g;
            } else {
                if (node == parent->right) {    // Case 2. left right
                    lRotate(root, parent);          // change case 2 to case 3
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
                setColor(parent, BLACK);
                setColor(uncle, BLACK);
                setColor(parent_g, RED);
                node = parent_g;
            } else {
                if (node == parent->left) {     // case 2. right left
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

void RBTree::fixDeletion(Node *&root, Node *&node) {
    if (root == nullptr)
        return;
    // get Child of node
    Node *child = node->left ? node->left : node->right;
    if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }
    if (child)
        child->parent = node->parent;
   
   if (BLACK == getColor(node)) {
       Node *parent = node->parent; // child may be nullptr
       Node *sibling = nullptr;
       while (child != root && BLACK == getColor(child)) {
           if (child == parent->left) {         // Case 1. RED
               sibling = parent->right;
               if (RED == getColor(sibling)) {
                   setColor(sibling, BLACK);
                   setColor(parent, RED);
                   lRotate(root, parent);
               } else {
                                                // Case 2. BLACK - BLACK - BLACK
                   if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                       setColor(sibling, RED);
                       if (RED == getColor(parent)) {
                           setColor(parent, BLACK);
                           break;
                       } else {
                           child = parent;
                           continue;
                       }
                                                // Case 3. BLACK - RED - BLACK
                   }else {
                       if (getColor(sibling->right) == BLACK) {
                           setColor(sibling->left, BLACK);
                           setColor(sibling, RED);
                           rRotate(root, sibling);
                           sibling = parent->right;
                       }                        // Case 4. BLACK - <> - RED
                       setColor(sibling, getColor(parent));
                       setColor(parent, BLACK);
                       setColor(sibling->right, BLACK);
                       lRotate(root, parent);
                       child = root;
                   }
               }
           } else {
               sibling = parent->left;
               if (getColor(sibling) == RED) {  // Case 1. RED
                   setColor(sibling, BLACK);
                   setColor(parent, RED);
                   rRotate(root, parent);
               } else {                         // Case 2. BLACK - BLACK - BLACK
                   if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (RED == getColor(parent)) {
                            setColor(parent, BLACK);
                            break;
                        } else {
                            child = parent;
                            continue;
                        }
                   } else {
                                                // Case 3. BLACK - BLACK - RED
                       if (BLACK == getColor(sibling->left)) {
                           setColor(sibling, RED);
                           setColor(sibling->right, BLACK);
                           lRotate(root, sibling);
                           sibling = parent->left;
                       }                        // Case 4. BLACK- RED - <>
                       setColor(sibling, getColor(parent));
                       setColor(parent, BLACK);
                       setColor(sibling->left, BLACK);
                       rRotate(root, parent);
                       child = root;
                   }
               }
           }           
       }
       setColor(child, BLACK);
   }
   free(node);
}

void RBTree::RBInsert(const int &key) {
    Node *node = new Node(key);
    root = BSTInsert(root, node);
    fixInsertion(root, node);
}

void RBTree::RBDelete(const int key) {
    Node *node = BSTDelete(root, key);
    fixDeletion(root, node);
}

int main(void) {
    RBTree tree;
 
    tree.RBInsert(12);
    tree.RBInsert(1);
    tree.RBInsert(9);
    tree.RBInsert(2);
    tree.RBInsert(0);
    tree.RBInsert(11);
    tree.RBInsert(7);
    tree.RBInsert(19);
    tree.RBInsert(4);
    tree.RBInsert(15);
    tree.RBInsert(18);
    tree.RBInsert(5);
    tree.RBInsert(14);
    tree.RBInsert(13);
    tree.RBInsert(10);
    tree.RBInsert(16);
    tree.RBInsert(6);
    tree.RBInsert(3);
    tree.RBInsert(8);
    tree.RBInsert(17); 
    
    tree.RBDelete(12);
    cout << "Inorder traversal of RBTree:\n";
    tree.inOrder();
    
    return 0;
}