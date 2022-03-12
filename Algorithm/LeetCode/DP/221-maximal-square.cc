/* Medium
Given an m x n binary matrix filled with 0's and 1's,
find the largest square containing only 1's and return its area.

Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4

Example 2:
Input: matrix = [["0","1"],["1","0"]]
Output: 1

Example 3:
Input: matrix = [["0"]]
Output: 0

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is '0' or '1'.

Rlatives:
085. Maximal Rectangle
764. Largest Plus Sign */

#include <vector>
#include <initializer_list>

using namespace std;

/* dp(i,j) = min(dp(i−1,j), dp(i−1,j−1), dp(i,j−1))+1
 * dp(i,j) represents the side length of the maximum square
 * whose bottom right corner is the cell with index (i,j) */

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;

        int RowSize = matrix.size();
        int ColSize = matrix[0].size();
        vector dp(ColSize+1, 0);
        int prev = 0;
        int maxLen = 0;

        for (int r = 1; r <= RowSize; ++r) {
            for (int c = 1; c <= ColSize; ++c) {
                int tmp = dp[c];
                if (matrix[r-1][c-1] == '1') {
                    dp[c] = min({dp[c], dp[c-1], prev}) + 1;
                    maxLen = max(maxLen, dp[c]);
                } else {
                    dp[c] = 0;
                }
                prev = tmp;
            }
        }

        return maxLen * maxLen;
    }
};

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        const auto RowSize = matrix.size();
        const auto ColSize = matrix[0].size();
        int maxLen = 0;

        vector<vector<int>> dp(RowSize+1, vector(ColSize+1, 0));

        for (auto r = 1; r <= RowSize; ++r) {
            for (auto c = 1; c <= ColSize; ++c) {
                if (matrix[r-1][c-1] == '1') {
                    dp[r][c] = 1 + min({dp[r-1][c-1], dp[r-1][c], dp[r][c-1]});
                    maxLen = max(maxLen, dp[r][c]);
                }
            }
        }

        return maxLen * maxLen;
    }
};