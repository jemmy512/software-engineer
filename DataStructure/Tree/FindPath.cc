/* Find a path summary equals to the expected value. */

#include <iostream>
#include <vector>

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

/**************************** Find Any Path ***********************************/

void FindPath(Tree* root,int expectedSum,int currentSum,vector<int>& path) {
    currentSum += root->data;
    path.push_back(root->data);

    if(currentSum == expectedSum){
        cout<<"A path is found: "<<endl;
        for(auto s : path){
            cout << s <<" ";
        }
        cout << endl;
        //找到一条路径返回继续查找
        path.pop_back();
        return;
    }

    if(root->left)
        FindPath(root->left, expectedSum, currentSum, path);
    if(root->right)
        FindPath(root->right, expectedSum, currentSum, path);

    path.pop_back();
}

void Path(Tree* root,int expectedSum) {
    if(root){
        vector<int> path;
        int currentSum = 0;
        FindPath(root, expectedSum, currentSum, path);

        Path(root->left, expectedSum);

        Path(root->right, expectedSum);
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

void findPath(BTNode *root, int curVal, int reqVal, vector<int> &vec) {
    curVal += root->data;
    vec.push_back(root->data);

    bool isLeaf = !root->left && !root->right;
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

bool hasPathSum(BTNode* root, int sum) {
    if (!root)
        return false;

    sum -= root->val;

    if (root->left == nullptr && root->right == nullptr)
        return sum == 0;

    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}

int main() {
    int arr[] = {3,2,5,8,4,7,6,9};
    BTNode *root = creatBTree(arr, 8);
    findPath(root, 29);

    return 0;
}