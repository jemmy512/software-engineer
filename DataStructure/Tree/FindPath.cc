/* Find vec path summary equals to the expected value. */

#include <iostream>
#include <vector>

using namespace std;

typedef struct Node_ {
    int val;
    struct node *left, *right;

    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
} Node;

Node *creatBTree(int vec[], int len) {
    Node *root, *prev, *cur, *n;
    root = new Node(vec[0]);

    for (int i = 1; i < len; ++i) {
        cur = root;
        n = new Node(vec[i]);

        while (cur) {
            prev = cur;
            cur = (cur->val > n->val) ? cur->left : cur->right;
        }
        if (prev->val > n->val)
            prev->left = n;
        else
            prev->right = n;
    }
    return root;
}

/**************************** Find Any Path ***********************************/

void doFindPathAny(Tree* root, int dstSum, int curSum, vector<int>& path) {
    curSum += root->val;
    path.push_back(root->val);

    if (curSum == dstSum) {
        cout << "A path is found: " << endl;
        for (auto s : path) {
            cout << s <<" ";
        }
        cout << endl;

        path.pop_back();
        return;
    }

    if (root->left)
        doFindPathAny(root->left, dstSum, curSum, path);
    if (root->right)
        doFindPathAny(root->right, dstSum, curSum, path);

    path.pop_back();
}

void findPathAny(Tree* root,int dstSum) {
    if (root) {
        vector<int> path;
        int curSum = 0;

        doFindPathAny(root, dstSum, curSum, path);

        findPathAny(root->left, dstSum);
        findPathAny(root->right, dstSum);
    }

}

/*

    int path(TreeNode *root, int curSum, int sum) {
        if (!root) return 0;
        curSum += root->val;
        return (curSum == sum) + path(root->left, curSum, sum) + path(root->right, curSum, sum);
    }

    int pathSum(TreeNode* root, int sum) {
        if (!root) return 0;
        return path(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }

*/


/**************************** Find Path from Root to Leaf *********************/

void doFindPathRootLeaf(Node *root, int curSum, int dstSum, vector<int> &vec) {
    if (!root) {
        return;
    }

    curSum += root->val;
    vec.push_back(root->val);

    const bool isLeaf = !root->left && !root->right;
    if (isLeaf && curSum == dstSum) {
        cout << "A path is found:\n";
        for (int i : vec)
            cout << i << " ";
        cout << endl;
    }

    doFindPathRootLeaf(root->left, curSum, dstSum, vec);
    doFindPathRootLeaf(root->right, curSum, dstSum, vec);

    vec.pop_back();
}

void findPathRootLeaf(Node *root, int dstSum) {
    if (root){
        vector<int> vec;
        int curSum = 0;
        doFindPathRootLeaf(root, curSum, dstSum, vec);
    }
}

bool hasPathSum(Node* root, int sum) {
    if (!root)
        return false;

    sum -= root->val;

    /*  n  left & right must be null at same time
        \
        p */
    if (root->left == nullptr && root->right == nullptr)
        return sum == 0;

    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}

int main() {
    int arr[] = {3,2,5,8,4,7,6,9};
    Node *root = creatBTree(arr, 8);
    findPathRootLeaf(root, 29);

    return 0;
}