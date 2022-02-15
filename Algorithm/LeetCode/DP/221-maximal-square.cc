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

        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        vector dp(colSize+1, 0);
        int prev = 0;
        int maxLen = 0;

        for (int row = 1; row <= rowSize; ++row) {
            for (int col = 1; col <= colSize; ++col) {
                int tmp = dp[col];
                if (matrix[row-1][col-1] == '1') {
                    dp[col] = min({dp[col], dp[col-1], prev}) + 1;
                    maxLen = max(maxLen, dp[col]);
                } else {
                    dp[col] = 0;
                }
                prev = tmp;
            }
        }

        return maxLen * maxLen;
    }
};