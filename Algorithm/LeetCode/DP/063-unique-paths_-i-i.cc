/*
A robot is located at the top-left corner of a rowSize x colSize grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to
reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?
        start
        +---------+----+----+----+----+----+
        |----|    |    |    |    |    |    |
        |----|    |    |    |    |    |    |
        +----------------------------------+
        |    |    |    |    |    |    |    |
        |    |    |    |    |    |    |    |
        +----------------------------------+
        |    |    |    |    |    |    |----|
        |    |    |    |    |    |    |----|
        +----+----+----+----+----+---------+
                                    finish

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: rowSize and colSize will be at most 100.

Example 1:

Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Relatives:
62. Unique Paths
63. Unique Paths II
980. Unique Paths III
64. Minimum Path Sum
174. Dungeon Game
741. Cherry Pickup */

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int rowSize = obstacleGrid.size();
        int colSize = obstacleGrid[0].size();
        vector<int> vec(colSize, 0);
        vec[0] = 1;

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (obstacleGrid[row][col]) {
                    vec[col] = 0;
                } else if (col > 0) {
                    vec[col] += vec[col-1];
                }
            }
        }

        return vec.back();
    }
};