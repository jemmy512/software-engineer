#include<iostream>
#include<deque>
#include<vector>
#include<iterator>

using namespace std;

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

int max(int a, int b) {
    return a > b ? a : b;
}

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

BTNode *insertNode(BTNode *node, int key) {
    if (!node)
        return newNode(key);
    if (key < node->data)
        node->left = insertNode(node->left, key);
    else if (key > node->data)
        node->right = insertNode(node->right, key);
    else 
        return node;
    
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    
    int balance = getBalance(node);
    // right right case
    if (balance > 1 && key > node->right->data)
        return rRotate(node);
    // left left case
    if (balance < -1 && key < node->left->data)
        return lRotate(node);
    // right left case
    if (balance > 1 && key < node->right->data) {
        node->right = rRotate(node->right);
        return lRotate(node);
    }
    // left rigth case
    if (balance < -1 && key > node->left->data) {
        node->left = lRotate(node->left);
        return rRotate(node);
    }
    
    return node;
}

int main(void) {
    int arr[] = {3, 2, 5, 8, 4, 7, 6, 9};
    
    BTNode *root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    //root = insertNode(root, 30);
    //root = insertNode(root, 40);
    //root = insertNode(root, 50);
    //root = insertNode(root, 25);
    
    inOrder(root);
}