/* Medium
Given a m x n grid filled with non-negative numbers, find a path from top
left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.

Relatives:
62. Unique Paths
63. Unique Paths II
980. Unique Paths III
64. Minimum Path Sum
174. Dungeon Game
741. Cherry Pickup */

class Solution {
public:
    int minPathSum(const vector<vector<int>>& grid) {
        int rowSize = grid.size();
        int colSize = grid[0].size();
        vector<int> sum(colSize, 0);
        sum[0] = grid[0][0];

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (row == 0) {
                    if (col == 0)
                        sum[col] = grid[row][col];
                    else
                        sum[col] = sum[col-1] + grid[row][col];
                } else if (col == 0) {
                    sum[col] = sum[col] + grid[row][col];
                } else {
                    sum[col] = grid[row][col] + min(sum[col], sum[col-1]);
                }
            }
        }

        return sum.back();
    }
};