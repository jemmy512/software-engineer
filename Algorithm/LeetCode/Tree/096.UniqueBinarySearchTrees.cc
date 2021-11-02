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

#include <vector>

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        Memo = vector(n+1, vector(n+1, 0));

        return count(1, n);
    }

private:
    int count(int beg, int end) {
        int ret = 1;

        if (beg > end)
            return ret;
        if (Memo[beg][end] != 0)
            return Memo[beg][end];

        for (auto i = beg; i <= end; ++i) {
            auto left = count(beg, i - 1);
            auto right = count(i + 1, end);
            ret += left * right;
        }

        Memo[beg][end] = ret;

        return ret;
    }

private:
    vector<vector<int>> Memo;
};