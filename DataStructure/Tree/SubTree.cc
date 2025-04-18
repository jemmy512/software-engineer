#include <iostream>

using namespace std;

typedef struct Node_ {
    int data;
    Node* left;
    Node* right;

    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
} Node;

Node *createTree(Node *root, int key) {
    if (!root) {
        return new Node(key);
    } else if (root->data > key) {
        root->left = createTree(root->left, key);
    } else if (root->data < key) {
        root->right = createTree(root->right, key);
    } else {
        return root;
    }
}

Node* createTree(int a[],int len)
{
    Node* root, *n, *cur, *prev;

    root = new Node(a[0]);

    for (int i = 1; i < len; i++) {
        cur = root;
        n = new Node(a[i]);

        while (cur) {
            prev = cur;
            if (cur->data > n->data)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (prev->data > n->data)
            prev->left = n;
        else
            prev->right = n;
    }

    return root;
}

bool isSubTree(Node* root, Node *sub) {
    if (!sub) return true;
    if (!root) return false;
    if (root->data != sub->data) return false;

    return isSubTree(root->left, sub->left) && isSubTree(root->right, sub->right);
}

bool hasSubTree(Node* root,Node* sub)
{
    bool result = false;

    if (root && sub) {
        if (root->data == sub->data)
            result = isSubTree(root, sub);
        else if (root->data > sub->data)
            result = hasSubTree(root->left, sub);
        else
            result = hasSubTree(root->right, sub);

        // if (!sub)
            // result = hasSubTree(root->right, sub);
    }

    return result;
}



void PrePrint(Node* root) {
    if (root!=NULL) {
        cout<<root->data<<" ";
        PrePrint(root->left);
        PrePrint(root->right);
    }
}

int main(void) {
    int a[8] = {3, 2, 5, 8, 4, 7, 6, 9};
    int b[4] = {8, 7, 6, 7};

    // Node* root = createTree(a,8);
    // Node* sub = createTree(b,4);
    Node *root = NULL;
    Node *sub = NULL;
    for (int i = 0; i < 8; ++i) {
        root = createTree(root, a[i]);
    }
    for (int i = 0; i < 4; ++i) {
        sub = createTree(sub, b[i]);
    }

    PrePrint(root);
    cout << endl;

    PrePrint(sub);
    cout << endl;

    bool result = hasSubTree(root, sub);
    cout<<(result ? "Congratulations,Tree1 has Tree2." : "Sorry,Tree1 doesn't has Tree2.") << endl;
    return 0;
}
