/* Hard
Given an n x n integer matrix grid, return the minimum sum of a falling path with non-zero shifts.

A falling path with non-zero shifts is a choice of exactly one element from each row of grid such
that no two elements chosen in adjacent rows are in the same column.

Example 1:
Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation:
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.

Example 2:
Input: grid = [[7]]
Output: 7

Constraints:
n == grid.length == grid[i].length
1 <= n <= 200
-99 <= grid[i][j] <= 99

Relatives:
931. Minimum Falling Path Sum
1289. Minimum Falling Path Sum II */

#include <vector>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        const auto rowSize = matrix.size();
        const auto colSize = matrix[0].size();

        for (auto row = 1; row < rowSize; ++row) {
            for (auto col = 0; col < colSize; ++col) {
                const auto tmp = matrix[row-1][col];
                matrix[row-1][col] = INT_MAX;
                matrix[row][col] += *min_element(matrix[row-1].cbegin(), matrix[row-1].cend());
                matrix[row-1][col] = tmp;
            }
        }

        return *min_element(matrix[rowSize-1].cbegin(), matrix[rowSize-1].cend());
    }
};

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

        auto minElem = INT_MAX;

        for (auto i = 0; i < ColSize; ++i) {
            if (i != col) {
                minElem = min(minElem, matrix[row][col] + dp(matrix, row-1, i));
            }
        }

        Memo[row][col] = minElem;

        return minElem;
    }

private:
    int RowSize{0};
    int ColSize{0};
    vector<vector<int>> Memo;
};