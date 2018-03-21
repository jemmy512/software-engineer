/*
*   Reference:  https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
*               https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
*/

#include<iostream>
#include<deque>
#include<vector>
#include<iterator>

using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct node {
    int data;
    int height;
    struct node *left, *right;
}BTNode;

BTNode *newNode(int key) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->data = key;
    node->height = 1;
    node->left = node->right = NULL;
    
    return node;
}

/*
*   Utility funtions to insertion and deletion
*/
int getHeight(BTNode *node) {
    if (!node)
        return 0;
    return node->height;
}

int getBalance(BTNode *node) {
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
void inOrder(BTNode *root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

BTNode *minNode(BTNode *node) {
    while (node->left)
        node = node->left;
    return node;
}

// right rotate the tree
BTNode *rRotate(BTNode *root) {
    BTNode *tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    tmp->height = max(getHeight(tmp->left), getHeight(tmp->right)) + 1;
    
    return tmp;
}

// left rotate the tree
BTNode *lRotate(BTNode *root) {
    BTNode *tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    tmp->height = max(getHeight(tmp->left), getHeight(tmp->right)) + 1;
    
    return tmp;
}

/*
*   Insert a new node to the AVL tree
*/
BTNode *insertNode(BTNode *node, int key) {
// 1. Perform normal BST insertion    
    if (!node)
        return newNode(key);
    if (key < node->data)
        node->left = insertNode(node->left, key);
    else if (key > node->data)
        node->right = insertNode(node->right, key);
    else 
        return node;
// 2. Updata height of this ancestor node    
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
// 3. Balance this node according to the balance factor    
    int balance = getBalance(node);
    // left left case
    if (balance > 1 && key < node->left->data)
        return rRotate(node);
    // right right case
    if (balance < -1 && key > node->right->data)
        return lRotate(node);
    // left rigth case
    if (balance > 1 && key > node->right->data) {
        node->left = lRotate(node->left);
        return rRotate(node);
    }
    // right left case
    if (balance < -1 && key < node->left->data) {
        node->right = rRotate(node->right);
        return lRotate(node);
    }
    
    return node;
}

/*
*   Remove a node from the AVL tree
*/

BTNode *deleteNode(BTNode *root, int key) {
// 1. Perform standard delete    
    if (!root)
        return NULL;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left && root->right) {    // root has two children
            root->data = minNode(root->right)->data;
            root->right = deleteNode(root->right, root->data);
        } else {                            // root has one or zero child
            BTNode *tmp = root->left ? root->left : root->right;
            if (tmp) {
                *root = *tmp;
            } else {
                tmp = root;
                root = NULL;
            }
            free(tmp);
        }
    }
    if (!root) // The tree only has one child
        return NULL;
// 2. Updata height    
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
// 3. Balance tree
    int balance  = getBalance(root);
    // left left 
    if (balance > 1 && getBalance(root->left) >= 0)
        return lRotate(root);
    // right right 
    if (balance < -1 && getBalance(root->right) <= 0)
        return rRotate(root);
    // left right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = lRotate(root->left);
        return rRotate(root);
    }
    // right left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rRotate(root->right);
        return lRotate(root);
    }
    
    return root;
}

int main(void) {    
    BTNode *root = NULL;
    root = insertNode(root, 9);
    root = insertNode(root, 5);
    root = insertNode(root, 10);
    root = insertNode(root, 0);
    root = insertNode(root, 6);
    root = insertNode(root, 11);
    root = insertNode(root, -1);
    root = insertNode(root, 1);
    root = insertNode(root, 2);
    
    inOrder(root);
    cout << endl;
    root = deleteNode(root, 10);
    inOrder(root);
}