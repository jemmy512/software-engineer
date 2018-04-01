/*
*   Reference: 
        https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
*       https://juejin.im/entry/58371f13a22b9d006882902d#%E7%BA%A2%E9%BB%91%E6%A0%91%E7%9A%84%E5
            %B9%B3%E8%A1%A1%E5%88%A0%E9%99%A4
*       http://www.cnblogs.com/skywang12345/p/3245399.html#a1
*       http://blog.csdn.net/weewqrer/article/details/51866488
*       https://blog.csdn.net/v_JULY_v/article/details/6284050
*/

#include<iostream>
#include<iomanip>
#include<array>
using namespace std;

enum Color {RED, BLACK};

class RBTree;

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    Node(int key) {
        color = RED;
        data = key;
    }
};

class RBTree {
private:
protected:
    Node *BSTDelete(RBTree *const&, int);
    Node *BSTInsert(RBTree *const&, Node *&);
    void rRotate(RBTree *const&, Node *&);
    void lRotate(RBTree *const&, Node *&);
    void fixDeletion(RBTree *const&, Node *&);
    void fixInsertion(RBTree *const&T, Node *&);
public:
    Node *root;
    Node *nil;
    RBTree() { 
        nil = new Node(0);
        nil->color = BLACK;
        nil->left = nil->right = nil->parent = nil;
        root = nil; 
    }
    ~RBTree() {
        delete nil;
    }
    void inOrder();
    void preOrder();
    void RBInsert(const int n);
    void RBDelete(const int key);
    Color getColor(Node *&node) {
        return node->color;
    }
    void setColor(Node *node, Color color) {
        if (nil == node)
            return;
        node->color = color;
    }
    void testRotate() {
        lRotate(this, root);
    }
};

Node *minNode(RBTree *const&T, Node *root) {
    // nil's left, right and parent point to nil itself, so it's no need to test root is nil or not
    while(T->nil != root->left)
        root = root->left;
    return root;
}

void inOrderUtil(RBTree *const&T, Node *root) {
    if (T->nil != root) {
        inOrderUtil(T, root->left);
        cout << setw(2) << root->data << "[" << root->color << "] ";
        inOrderUtil(T, root->right);
    }
}

void preOrderUtil(RBTree *const&T, Node *root) {
    if (T->nil != root) {
        cout << setw(2) << root->data << "[" << root->color << "] ";
        preOrderUtil(T, root->left);
        preOrderUtil(T, root->right);
    }
}

void RBTree::inOrder() { inOrderUtil(this, root); }
void RBTree::preOrder() { preOrderUtil(this, root); }

void RBTree::lRotate(RBTree *const&T, Node *&node) {
    Node *root = T->root;
    Node *tmp = node->right;
    
    if (tmp == T->nil)  // J: needed?
        return;
    
    node->right = tmp->left;
    if (node->right != T->nil)         // 1. modify node->right
        node->right->parent = node;
    
    if (root == node)                   // 2. modify node->parent
        T->root = tmp;
    else if (node == node->parent->left) 
        node->parent->left = tmp;
    else 
        node->parent->right = tmp;
    
    tmp->left = node;                   // 3. modify tmp
    tmp->parent = node->parent;
    node->parent = tmp;                 // 4. modify node
} 

void RBTree::rRotate(RBTree *const&T, Node *&node) {
    Node *root = T->root;
    Node *tmp = node->left;
    
    if (tmp == T->nil)  // J: needed?
        return;
    
    node->left = tmp->right;            // 1. modify node->left
    if (node->left != T->nil)
        node->left->parent = node;
    
    if (node == root)                   // 2. modify node->parent
        T->root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else 
        node->parent->right = tmp;
    
    tmp->parent = node->parent;         // 3. modify tmp
    tmp->right = node;
    node->parent = tmp;                 // 4. modify node
}

Node *RBTree::BSTInsert(RBTree *const&T, Node *&node) {
    Node *root = T->root;
    Node *tmp = root;
    if (T->nil == node)
        return T->nil;
    
    // if (node->data < root->data) {      // 1. left insert
        // root->left = BSTInsert(root->left, node);
        // root->left->parent = root;
    // } else if (node->data > root->data){// 2. right inset
        // root->right = BSTInsert(root->right, node);
        // root->right->parent = root;
    // }
    
    while (root != T->nil) {
        tmp = root;
        if (node->data < root->data)
            root = root->left;              // 1. left insert
        else if (node->data > root->data)
            root = root->right;             // 2. right insert
        else 
            return T->nil;                  // 3. no insert
    }
    if (tmp == T->nil)
        T->root = node;
    else if (node->data < tmp->data)
        tmp->left = node;
    else if (node->data > tmp->data)
        tmp->right = node;
    node->parent = tmp;
    return node;                        
}

Node *RBTree::BSTDelete(RBTree *const&T, int key) {
    if (T->nil == T->root)
        return T->nil;
    // if (key == root->data) {
        // if (root->left && root->right) {// 1. has two children
            // root->data = minNode(root->right)->data;
            // return BSTDelete(root->right, root->data);
        // } else {                        // 2. has one or zero child
            // return root;
        // }
    // } else if (key < root->data){
        // return BSTDelete(root->left, key);
    // } else {
        // return BSTDelete(root->right, key);
    // }
    Node *root = T->root;
    while (root != T->nil) {
        if (key < root->data)
            root = root->left;
        else if (key > root->data)
            root = root->right;
        else {
            Node *tmp = root;
            if (tmp->left != T->nil && tmp->right != T->nil) { // when both left and right is nil they equals.
                root = minNode(T, tmp->right);
                tmp->data = root->data;                
            }
            return root;                    // root has one or zero child, return directly
        }
    }
    return T->nil;
}

void RBTree::fixInsertion(RBTree *const&T, Node *&node) {
    Node *parent, *parent_g, *uncle;
    parent = parent_g = uncle = T->nil;
    
    while ((node != T->root) && (getColor(node) == RED) && (getColor(node->parent) == RED)) {
        parent = node->parent;
        parent_g = parent->parent;
        
// Case A: parent is on the left of the parent_g -------------------------------
        if (parent == parent_g->left) {
            uncle = parent_g->right;
            if (RED == getColor(uncle)) { // Case 1. uncle color is red
                setColor(parent, BLACK);
                setColor(uncle, BLACK);
                setColor(parent_g, RED);
                node = parent_g;
            } else {
                if (node == parent->right) {    // Case 2. left right
                    lRotate(T, parent);          // change case 2 to case 3
                    node = parent; 
                    parent = node->parent;
                }
                rRotate(T, parent_g);        // Case 3. left left
                swap(parent->color, parent_g->color);
                node = parent;
            }
// Case B: parent is on the right of the parent_g ------------------------------
        } else { 
            uncle = parent_g->left;
            if (RED == uncle->color) { // Case 1. uncle is red
                setColor(parent, BLACK);
                setColor(uncle, BLACK);
                setColor(parent_g, RED);
                node = parent_g;
            } else {
                if (node == parent->left) {     // case 2. right left
                    rRotate(T, parent);
                    node = parent;
                    parent = node->parent;
                }
                lRotate(T, parent_g);        // case 3. right right
                swap(parent->color, parent_g->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

void RBTree::fixDeletion(RBTree *const&T, Node *&node) {
    if (T->root == T->nil || node == T->nil)
        return;
    // get Child of node
    Node *child = node->left != T->nil ? node->left : node->right;
    
    if (T->root == node)
        T->root = child;
    else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }
    child->parent = node->parent;
    
   if (BLACK == getColor(node)) {
       while (child != T->root && BLACK == getColor(child)) {
           Node *parent = child->parent; // child may be nullptr
           Node *sibling = T->nil;
           if (child == parent->left) {         // Case 1. RED
               sibling = parent->right;
               if (RED == getColor(sibling)) {
                   // setColor(sibling, BLACK);
                   // setColor(parent, RED);
                   swap(sibling->color, parent->color);
                   lRotate(T, parent);
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
                           // setColor(sibling->left, BLACK);
                           // setColor(sibling, RED);
                           swap(sibling->left->color, sibling->color);
                           rRotate(T, sibling);
                           sibling = parent->right;
                       }                        // Case 4. BLACK - <> - RED
                       // setColor(sibling, getColor(parent));
                       // setColor(parent, BLACK);
                       swap(sibling->color, parent->color);
                       setColor(sibling->right, BLACK);
                       lRotate(T, parent);
                       child = T->root;
                   }
               }
           } else {
               sibling = parent->left;
               if (getColor(sibling) == RED) {  // Case 1. RED
                   // setColor(sibling, BLACK);
                   // setColor(parent, RED);
                   swap(sibling->color, parent->color);
                   rRotate(T, parent);
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
                           // setColor(sibling, RED);
                           // setColor(sibling->right, BLACK);
                           swap(sibling->color, sibling->right->color);
                           lRotate(T, sibling);
                           sibling = parent->left;
                       }                        // Case 4. BLACK- RED - <>
                       // setColor(sibling, getColor(parent));
                       // setColor(parent, BLACK);
                       swap(sibling->color, parent->color);
                       setColor(sibling->left, BLACK);
                       rRotate(T, parent);
                       child = T->root;
                   }
               }
           }           
       }
       setColor(child, BLACK);
   }
   delete(node);
}

void RBTree::RBInsert(const int key) {
    Node *node = new Node(key);
    node->left = node->right = node->parent = nil;
    
    node = BSTInsert(this, node);
    fixInsertion(this, node);
}

void RBTree::RBDelete(const int key) {
    Node *node = BSTDelete(this, key);
    fixDeletion(this, node);
}

int main(void) {
    RBTree *tree = new RBTree();
 
    array<int, 20> arr = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
    
    for (int i = 0; i < arr.size(); ++i) {
        tree->RBInsert(arr[i]);
    }
    tree->RBInsert(4);
    cout << "Insetion. Inorder traversal of RBTree:\n";
    tree->inOrder();
    cout << endl;
    tree->preOrder();
    
    // tree->RBDelete(9);
    for (int i = 0; i < arr.size(); ++i) {
        tree->RBDelete(arr[i]);
        cout << "D<" << setw(2) << arr[i] << "> ";
        tree->inOrder();
        cout << endl;
    }
    cout << "\nDeletion. Inorder traversal of RBTree:\n";
    tree->inOrder();
    return 0;
}