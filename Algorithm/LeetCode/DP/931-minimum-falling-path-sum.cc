/* Medium
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row
that is either directly below or diagonally left/right.
Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).


Example 1:
Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.

Example 2:
Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.

Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 100
-100 <= matrix[i][j] <= 100

Relatives:
931. Minimum Falling Path Sum
1289. Minimum Falling Path Sum II */

#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        auto Result = INT_MAX;
        RowSize = matrix.size();
        ColSize = matrix[0].size();
        Memo.resize(RowSize, vector(ColSize, INT_MAX));

        for (auto col = 0; col < ColSize; ++col) {
            Result = min(Result, dp(matrix, RowSize - 1, col));
        }

        return Result;
    }

private:
    int dp(const vector<vector<int>>& matrix, int row, int col) {
        if (row < 0 || col < 0 || row >= RowSize || col >= ColSize)
            return INT_MAX;

        if (row == 0)
            return matrix[0][col];

        if (Memo[row][col] != INT_MAX)
            return Memo[row][col];

        return Memo[row][col] = matrix[row][col] + min({
            dp(matrix, row-1, col),
            dp(matrix, row-1, col-1),
            dp(matrix, row-1, col+1)
        });
    }

private:
    int RowSize{0};
    int ColSize{0};
    vector<vector<int>> Memo;
};