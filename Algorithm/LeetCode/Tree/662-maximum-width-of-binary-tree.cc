/* Medium
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes
(the leftmost and rightmost non-null nodes),
where the null nodes between the end-nodes that would be present in a complete binary tree
extending down to that level are also counted long longo the length calculation.

It is guaranteed that the answer will in the range of a 32-bit signed long longeger.

Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

Example 2:
Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

Example 3:
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2).


Constralong longs:
The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100 */

#include <utility>
#include <queue>

using namespace std;

struct TreeNode {
    long long val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(long long x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(long long x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    using Node = pair<TreeNode*, long long>;

    int widthOfBinaryTree(TreeNode* root) {
        if (!root)
            return 0;

        long long maxWidth = 0;
        queue<Node> que;
        que.push({root, 1});

        while (!que.empty()) {
            long long beg = 0, end = 0;
            const auto size = que.size();

            for (auto i = 0; i < size; ++i) {
                auto [node, id] = que.front();
                que.pop();

                if (i == 0)
                    beg = id;
                if (i == size - 1)
                    end = id;

                if (node->left)
                    que.push({node->left, 2 * id});
                if (node->right)
                    que.push({node->right, 2 * id + 1});

                maxWidth = max(maxWidth, end - beg + 1);
            }
        }

        return maxWidth;
    }
};

class Solution {
public:
    using Node = pair<TreeNode*, long long>;

    int widthOfBinaryTree(TreeNode* root) {
        if (!root)
            return 0;

        dfs(root, 1, 1);

        return MaxWidth;
    }

private:
    void dfs(TreeNode* node, int id, int depth) {
        if (!node)
            return;

        if (LevelBegId.size() == depth - 1) {
            LevelBegId.push_back(id);
        } else {
            MaxWidth = max(MaxWidth, id - LevelBegId[depth-1] + 1);
        }

        dfs(node->left, 2 * id, depth + 1);
        dfs(node->right, 2 * id + 1, depth + 1);
    }

private:
    int MaxWidth = 1;
    vector<int> LevelBegId;
};