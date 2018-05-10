#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode (int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *insertNode(TreeNode *root, int key) {
    if (!root) 
        return (new TreeNode(key));
    
    if (key < root->val) 
        root->left = insertNode(root->left, key);
    else if (key > root->val) 
        root->right = insertNode(root->right, key);
     
    return root;
}

// Refer: http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
/**************************** Morris traversal *********************************/

void MorrisInOrderTraverse(TreeNode *root) {
    TreeNode *cur = root, *prev = NULL;
    while (cur) {
        if (cur->left == NULL) {        // The left subtree has not been traversed
            cout << cur->val << " ";
            cur = cur->right;
        } else {
            prev = cur->left;
            while (prev->right && prev->right != cur)
                prev = prev->right;
            
            if (prev->right) {
                prev->right = NULL;
                cout << cur->val << " ";
                cur = cur->right;
            } else {                    // The left subtree has been traversed
                prev->right = cur;
                cur = cur->left;
            }
        }
    }
}

void MorrisPreOrderTraverse(TreeNode *root) {
    TreeNode *cur = root, *prev = NULL;
    while (cur) {
        if (cur->left == NULL) {
            cout << cur->val << " ";
            cur = cur->right;
        } else {
            prev = cur->left;
            while (prev->right && prev->right != cur)
                prev = prev->right;
            if (prev->right) {
                prev->right = NULL;
                cur = cur->right;
            } else {
                cout << cur->val << " ";
                prev->right = cur;
                cur = cur->left;
            }
        }
    }
}

void reverseTree(TreeNode *from, TreeNode *to) {
    
    TreeNode *x = from, *y = from->right, *z;
    while (x != to) {
        z = y->right;
        y->right = x;
        x = y;
        y = z;
    }
}

void printReversedTree(TreeNode *from, TreeNode *to) {
    reverseTree(from, to);
    TreeNode *p = to;
    while (true) {
        cout << p->val << " ";
        if (p == from)
            break;
        p = p->right;
    }
    
    reverseTree(to, from);
}

void MorrisPostOrderTraversal(TreeNode *root) {
    if (!root) return;
    TreeNode dummy(0);
    dummy.left = root;
    TreeNode *cur = &dummy, *prev = NULL;
    while (cur) {
        if (cur->left == NULL) {
            cur = cur->right;
        } else {
            prev = cur->left;
            while (prev->right && prev->right != cur) 
                prev = prev->right;
            if (prev->right) {
                printReversedTree(cur->left, prev);
                prev->right = NULL;
                cur = cur->right;
            } else {
                prev->right = cur;
                cur = cur->left;
            }
        }
    }
}

/**************************** pre-order traversal ******************************/

void preOrderRecursive(TreeNode *root) {
    if (root) {
        cout << root->val << " ";
        preOrderRecursive(root->left);
        preOrderRecursive(root->right);
    }
}

void preOrderIterator(TreeNode *root) {
    stack<TreeNode *> stk;
    TreeNode *cur = root;
    while (!stk.empty() || cur) {
        if (cur) {
            cout << cur->val << " ";
            stk.push(cur);
            cur = cur->left;
        } else {
            cur = stk.top()->right;
            stk.pop();
        }
    }
}

/**************************** in-order traversal *******************************/

void inOrderRecursive(TreeNode *root) {                    // recursive version
    if (root) {
        inOrderRecursive(root->left);
        cout << root->val << " ";
        inOrderRecursive(root->right);
    }
}

void inOrderIterator(TreeNode* root) {  // iterator version
    stack<TreeNode *> stk;
    TreeNode *cur = root;
    while (!stk.empty() || cur) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        } else {
            cout << stk.top()->val << " ";
            cur = stk.top()->right;
            stk.pop();
        }
    }
}

/**************************** post-order traversal ******************************/

void postOrderRecursive(TreeNode *root) {
    if (root) {
        postOrderRecursive(root->left);
        postOrderRecursive(root->right);
        cout << root->val << " ";
    }
}

void postOrderIterator(TreeNode *root) {
    if (!root) return ;
    
    stack<TreeNode *> stk;
    TreeNode *cur = root;
    do {
        while (cur) {
            if (cur->right)
                stk.push(cur->right);
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        // when stack is empty, the behavior of stack.top() is undefined
        if (cur->right && !stk.empty() && stk.top() == cur->right ) {
            stk.pop();
            stk.push(cur);
            cur = cur->right;
        } else {
            cout << cur->val << " ";
            cur = NULL;
        }
    } while (!stk.empty());
}

int main() {
    vector<int> vec = {6,2,1,4,3,5,7,9,8};
    TreeNode *root = NULL;
    for (int i : vec) {
        root = insertNode(root, i);
    }
    cout << "****************" << endl;
    // cout << "PreOrder: ";
    // preOrderRecursive(root) ;
    // cout << endl;
    // cout << "InOrder: ";
    // inOrderIterator(root);
    // cout << endl;
    cout << "PostOrder: " ;
    postOrderIterator(root);
    cout << endl;
    // inOrderRecursive(root);
    // MorrisInOrderTraverse(root);
    // cout << endl;
    // MorrisPreOrderTraverse(root);
    // cout << endl;
    MorrisPostOrderTraversal(root);
    cout << endl;
}