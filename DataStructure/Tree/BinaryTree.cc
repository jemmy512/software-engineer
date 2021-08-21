#include<iostream>
#include<deque>
#include<queue>
#include<stack>
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

BTNode *insert(BTNode *root, int key) {
    if (!root) {
        BTNode *tmp = (BTNode *)malloc(sizeof(BTNode));
        tmp->data = key;
        tmp->left = tmp->right =  NULL;
        return tmp;
    }
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    
    return root;
}

/************* Level Tranversal ***********************************************/

void bfs(BTNode *root) {
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

vector<vector<int>> bfs(TreeNode* root) {
    vector<vector<int>> vvec;
    if (!root) return vvec;
    
    vector<int> row;
    queue<TreeNode *> nodes;
    TreeNode *cur = root, *pre_last = root, *last;
    nodes.push(root);
    while (!nodes.empty()) {
        cur = nodes.front();
        row.push_back(cur->val);
        if (cur->left) {
            nodes.push(cur->left);
            last = cur->left;
        }
        if (cur->right) {
            nodes.push(cur->right);
            last = cur->right;
        }
        if (cur == pre_last) {
            vvec.push_back(row);
            row.clear();
            pre_last = last;
        }
        nodes.pop();
    }
    
    return vvec;
}

/************* Mirror Reversal ************************************************/

void mirrorReversal(BTNode *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return;
    BTNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    
    mirrorReversal(root->left);
    mirrorReversal(root->right);
}

int LeafCount(BTnode *root){
	if(!root) return 0;
	int ll = LeafCount(root->left);
	int rr = LeafCount(root->right);
	return ll + rr + (!root->left && !root->right);
}

int NodeCount(BTnode* root){
    if(!root) return 0;
    int ll = NodeCount(root->left);
    int rr = NodeCount(root->right);
    return ll + rr + 1;
}

int LevelCount(BTnode *root){
	if(!root) return 0;
	int ll = LeafCount(root->left);
	int rr = LeafCount(root->right);
	return ll > rr ? (ll+1) : (rr+1);
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
    while (root->left)
        root = root->left;
    return root;
}

BTNode *deleteBTree(BTNode *root, int key) {
    if (!root)
        return NULL;
    if (key == root->data) {
        if (root->left && root->right) {    // Case 3. Two children
            root->data = minBTNode(root->right)->data;
            root->right = deleteBTree(root->right, root->data);
        } else {                            
            BTNode *tmp = root->left ? root->left : root->right;
            if (tmp) {                      // Case 2. One child
                *root = *tmp; // copy from tmp to root
            } else {                        // Case 1. No child
                tmp = root;
                root = NULL;
            }
            free(tmp);
        }
    } else if (key < root->data){
        root->left = deleteBTree(root->left, key);
    } else {
        root->right = deleteBTree(root->right, key);
    }
    return root;
}

int main() {
    int arr[8] = {3, 2, 5, 8, 4, 7, 6, 9};
    BTNode *root = creatBTree(arr, 8);
    
    cout << "preorder traverse tree: \n";
    preOrderRecursive(root);
    cout << endl;
    preOrderIterator(root);
    cout << endl;
    
    cout << "\nin-order travese tree:\n";
    inOrderRecursive(root);
    cout << endl;
    inOrderIterator(root);
    cout << endl;
    
    cout << "\npost-order traverse tree:\n";
    postOrderRecursive(root);
    cout << endl;
    postOrderIterator(root);
    cout << endl;

    cout << "\ninsert btree: "; 
    insertBTree(root, 1);
    
    cout << "\ntraverse tree by level: \n";
    bfs(root);
    
    cout << "\nMirror reverse Tree: \n";
    //mirrorReversal(root);
    //preOrder(root);
    
    cout << "\nAfter delete, in-order travese tree:\n";
    root = deleteBTree(root, 3);
    inOrderRecursive(root);
    
    freeTree(root);
    return 0;
}