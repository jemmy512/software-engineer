/* Hard
You are given k identical eggs and you have access to a building with n floors labeled from 1 to n.

You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor higher than f will break,
and any egg dropped at or below floor f will not break.

Each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n).
If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.

Return the minimum number of moves that you need to determine with certainty what the value of f is.

Example 1:
Input: k = 1, n = 2
Output: 2
Explanation:
Drop the egg from floor 1. If it breaks, we know that f = 0.
Otherwise, drop the egg from floor 2. If it breaks, we know that f = 1.
If it does not break, then we know f = 2.
Hence, we need at minimum 2 moves to determine with certainty what the value of f is.

Example 2:
Input: k = 2, n = 6
Output: 3
Example 3:

Input: k = 3, n = 14
Output: 4

Constraints:
1 <= k <= 100
1 <= n <= 10^4 */

#include <climits>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

// O(K*N^2)
class Solution {
public:
    int superEggDrop(int k, int n) {
        return dp(k, n);
    }

private:
    // k egges can drop at most n times
    int dp(int k, int n) {
        if (k == 1) return n;
        if (n == 0) return 0;

        const auto key = k * 10000 + n;
        if (Memo.find(key) != Memo.end()) {
            return Memo[key];
        }

        auto ret = INT_MAX;

        for (auto i = 1; i <= n; ++i) {
            const auto subProblem = 1 + max(dp(k, n - i), dp(k - 1, i - 1));
            ret = min(ret, subProblem);
        }

        Memo[key] = ret;

        return ret;
    }

private:
    unordered_map<int, int> Memo;
};

// optimization with binary search
// O(K*N*logN)
class Solution {
public:
    int superEggDrop(int k, int n) {
        return dp(k, n);
    }

private:
    int dp(int k, int n) {
        if (k == 1) return n;
        if (n == 0) return 0;

        const auto key = k * 10000 + n;
        if (Memo.find(key) != Memo.end()) {
            return Memo[key];
        }

        auto beg = 1;
        auto end = n;
        auto ret = INT_MAX;

        while (beg <= end) {
            const auto mid  = beg + (end - beg) / 2;
            const auto broken = dp(k-1, mid - 1);
            const auto notBroken = dp(k, n - mid);

            if (broken > notBroken) {
                end = mid - 1;
                ret = min(ret, broken + 1);
            } else {
                beg = mid + 1;
                ret = min(ret, notBroken + 1);
            }
        }

        Memo[key] = ret;

        return ret;
    }

private:
    unordered_map<int, int> Memo;
};

// rewrite state transition equation
// O(KN)
class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<vector<int>> dp(k+1, vector(n+1, 0));
        /* base case:
         * dp[0][.] = 0
         * dp[.][0] = 0 */

        auto m = 0;

        /* there are k eggs, it is allowed to drop eggs at most m times, it can test n floors */
        while (dp[k][m] < n) {
            ++m;
            for (auto i = 1; i <= k; ++i) {
                dp[i][m] = dp[i][m-1] + dp[i-1][m-1] + 1;
            }
        }

        return m;
    }
};