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

/* For G(n), it does not matter the content of the sequence, but the length of the sequence. Therefore
F(3,7)=G(2)⋅G(4).
G(n) = <i=1, n>∑F(i,n)
G(0)=1, G(1)=1
F(i,n) = G(i−1)⋅G(n−i)
G(n) = <i=1, n>∑[G(i−1)⋅G(n−i)] */
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (auto i = 2; i <= n; ++i) {
            for (auto j = 1; j <= i; ++j) {
                dp[i] += dp[j-1] * dp[i-j];
            }
        }

        return dp[n];
    }
};

class Solution {
public:
    int numTrees(int n) {
        Memo = vector(n+1, vector(n+1, 0));

        return count(1, n);
    }

private:
    int count(int beg, int end) {
        if (beg > end)
            return 1;

        if (Memo[beg][end] != 0)
            return Memo[beg][end];

        int cnt = 0;

        for (auto i = beg; i <= end; ++i) {
            auto left = count(beg, i - 1);
            auto right = count(i + 1, end);
            cnt += left * right;
        }

        Memo[beg][end] = cnt;

        return cnt;
    }

private:
    vector<vector<int>> Memo;
};