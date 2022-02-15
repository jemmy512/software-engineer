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

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0 or 1.

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
        int result = 0;
    
        if (grid.empty())
            return result;

        _RowSize = grid.size();
        _ColSize = grid[0].size();

        for (auto row = 0; row < _RowSize; ++row) {
            for (auto col = 0; col < _ColSize; ++col) {
                if (grid[row][col]) {
                    result = max(result, dfs(grid, row, col));
                }
            }
        }

        return result;
    }

private:
    int dfs(vector<vector<int>>& grid, int row, int col) {
        int result = 0;
    
        if (row < 0 || row >= _RowSize || col < 0 || col >= _ColSize || grid[row][col] == 0)
            return result;

        result = 1;
        grid[row][col] = 0;

        for (const auto& [r, c] : _Directions) {
            result += dfs(grid, row+r, col+c);
        }

        return result;
    }

private:
    int _RowSize{0};
    int _ColSize{0};
    const vector<pair<int, int>> _Directions {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
    };
};