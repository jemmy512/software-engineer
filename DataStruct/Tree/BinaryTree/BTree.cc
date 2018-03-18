#include<iostream>
#include<deque>
#include<vector>
#include<iterator>

using namespace std;

typedef struct node {
    int data;
    struct node *left, *right;
}BTNode;

BTNode *creatBTree(int a[], int n) {
    BTNode *root, *p, *c, *pn;
    root = (BTNode *)malloc(sizeof(BTNode));
    root->data = a[0];
    root->left = root->right = NULL;
    
    for (int i = 1; i < n; ++i) {
        pn = (BTNode *)malloc(sizeof(BTNode));
        pn->data = a[i];
        pn->left = pn->right = NULL;
        
        c = root;
        while (c) {
            p = c;
            c = c->data > pn->data ? c->left : c->right;
        }
        if (p->data > pn->data)
            p->left = pn;
        else 
            p->right = pn;
    }
    return root;
}

// preorder traversal the tree according to root element
void preOrder(BTNode *root) {
    if (root) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// in-order traversal the tree according to root element
void inOrder(BTNode *root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// post-order traversal the tree according to root element
void postOrder(BTNode *root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}


// level traversal the tree
void levelOrder(BTNode *root) {
    deque<BTNode *> deq;
    vector<int> vec;
    
    deq.push_back(root);
    while (deq.size()) {
        BTNode *node = deq.front();
        deq.pop_front();
        if (node->left)
            deq.push_back(node->left);
        if (node->right)
            deq.push_back(node->right);
        vec.push_back(node->data);
    }
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void mirrorReversal(BTNode *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return;
    BTNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    
    mirrorReversal(root->left);
    mirrorReversal(root->right);
}

void freeTree(BTNode *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

bool searchBTree(BTNode *root, BTNode *prev, int key, BTNode **ret) {
    if (!root) {
        *ret = prev;
        return false;
    } else if (root->data == key) {
        *ret = root;
        return true;
    } else if (root->data > key) {
        searchBTree(root->left, root, key, ret);
    } else {
        searchBTree(root->right, root, key, ret);
    }
}

void insertBTree(BTNode *root, int key) {
    BTNode *ret = NULL;
    if (!searchBTree(root, NULL, key, &ret)) {
        BTNode *tmp = (BTNode *)malloc(sizeof(BTNode));
        tmp->data = key;
        tmp->left = tmp->right = NULL;
        
        if (!ret) {
            root = tmp;
        } else if (root->data > key) {
            ret->left = tmp;
        } else {
            ret->right = tmp;
        }
    } else {
        fprintf(stderr, "[%d] already exits\n", key);
    }
}

/*
*   delete node from BST, this is much more complicated
*   Some cases we need to care:
*       1. Node has no children
*       2. Node has one children [left or right]
*       3. Node has two children 
*/
BTNode *minBTNode(BTNode *root) {
    if (!root->left)
        return root;
    return minBTNode(root->left);
}

BTNode *deleteBTree(BTNode *root, BTNode *prev, int key) {
    if (!root)
        return NULL;
    if (root->data == key) {
        if (root->left && root->right) { Case 3. Two children
            
        } else if (prev->left == root) { Case 2. One children-left
            prev->left = root->left ? root->left : root->right;
            return root;
        } else if (prev->right == root) { Case 2. One children-right
            prev->right = root->right ? right : root->left;
            return root;
        }
    } else if (root->data > key){
        
    } else {
        
    }
}

// we need to handle the situation of root node specially
void deleteBTree(BTNode *root, int key) {        
    if (!root)
        return;
    BTNode *rm = NULL;
    if (root->data == key) {
        BTNode *tmp = (BTNode *)malloc(sizeof(BTNode));
        tmp->data = key + 1;
        tmp->left = root;
        tmp->right = NULL;
        rm = deleteBTree(root, tmp, key);
        root->tmp->left;
        free(tmp);
    } else if (root->data > key) {
        rm = deleteBTree(root->left, root, key);
    } else {
        rm = deleteBTree(root->right, root, key);
    }
    if (rm)
        free(rm);
}  


int main() {
    int arr[8] = {3, 2, 5, 8, 4, 7, 6, 9};
    BTNode *root = creatBTree(arr, 8);
    
    cout << "preorder traversal tree: \n";
    preOrder(root);
    
    cout << "\nin-order travese tree:\n";
    inOrder(root);
    
    cout << "\npost-order traverse tree:\n";
    postOrder(root);

    cout << "\ninsert btree: "; 
    //insertBTree(root, 1);
    deleteBTree(root, NULL, 5);
    
    cout << "\ntraverse tree by level: \n";
    levelOrder(root);
    
    cout << "\nMirror reverse Tree: \n";
    mirrorReversal(root);
    preOrder(root);
    
    
    freeTree(root);
    return 0;
}