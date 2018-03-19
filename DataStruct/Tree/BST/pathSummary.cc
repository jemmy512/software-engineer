/* 
*   Find a path from root node to leaf node and it's summary equals to the expected value.   
*/
#include<iostream>
#include<vector>

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

void findPath(BTNode *root, int curVal, int reqVal, vector<int> &vec) {
    bool isLeaf = !root->left && !root->right;
    curVal += root->data;
    vec.push_back(root->data);
    if (curVal == reqVal && isLeaf) {
        cout << "A path is found:\n";
        for (int i : vec)
            cout << i << " ";
        cout << endl;
    }
    if (root->left)
        findPath(root->left, curVal, reqVal, vec);
    if (root->right)
        findPath(root->right, curVal, reqVal, vec);
    vec.pop_back();
}

void findPath(BTNode *root, int reqVal) {
    if (root == NULL)
        return;
    vector<int> vec;
    int curVal = 0;
    findPath(root, curVal, reqVal, vec);
}

int main() {
    int arr[] = {10, 5, 12, 4, 7};
    BTNode *root = creatBTree(arr, 5);
    findPath(root, 22);
    
    return 0;
}