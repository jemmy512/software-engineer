/* Medium
Given an integer n, return the number of structurally unique BST's (binary search trees)
which has exactly n nodes of unique values from 1 to n.

Example 1:
Input: n = 3
Output: 5

Example 2:
Input: n = 1
Output: 1

Constraints:
1 <= n <= 19 */

#include <map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    using Container = std::shared_ptr<vector<TreeNode*>>;

public:
    vector<TreeNode*> generateTrees(int n) {
        Memo = vector(n+1, vector(n+1, Container()));
        return *(build(1, n));
    }

private:
    Container build(int beg, int end) {
        auto ret = std::make_shared<vector<TreeNode*>>();

        if (beg > end) {
            ret->emplace_back(nullptr);
            return ret;
        }

        if (Memo[beg][end] != nullptr) {
            return Memo[beg][end];
        }

        for (auto i = beg; i <= end; ++i) {
            auto left = build(beg, i - 1);
            auto right = build(i + 1, end);

            for (const auto& lhs : *left) {
                for (const auto& rhs : *right) {
                    ret->emplace_back(new TreeNode(i, lhs, rhs));
                }
            }
        }

        Memo[beg][end] = ret;

        return ret;
    }

private:
    vector<vector<Container>> Memo;
};