/* Medium
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land)
connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
Example 2:

[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.

Relatives:
130. Surrounded Regions
200. Number of Islands
286. Walls and Gates
305. Number of Islands II
323. Number of Connected Components in an Undirected Graph
694. Number of Distinct Islands
695. Max Area of Island */

#include <vector>

using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;

        int ret = 0;
        rowSize = grid.size();
        colSize = grid[0].size();

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (grid[row][col]) {
                    ret = max(ret, dfs(grid, row, col));
                }
            }
        }

        return ret;
    }

private:
    int dfs(vector<vector<int>>& grid, int row, int col) {
        if (row < 0 || col < 0 || row >= rowSize || col >= colSize || !grid[row][col])
            return 0;

        grid[row][col] = 0;
        int ret = 1;

        for (const auto& [r, c] : directions) {
            ret += dfs(grid, row + r, col + c);
        }

        return ret;
    }

private:
    int rowSize{0};
    int colSize{0};

    vector<pair<int, int>> directions {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };
};