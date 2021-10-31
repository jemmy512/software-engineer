/* Medium
You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.

A move consists of walking from one land cell to another adjacent (4-directionally)
land cell or walking off the boundary of the grid.

Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

Example 1:
Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.

Example 2:
Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: All 1s are either on the boundary or can reach the boundary.


Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 500
grid[i][j] is either 0 or 1.

Relatives:
130. Surrounded Regions
200. Number of Islands
305. Number of Islands II
286. Walls and Gates
323. Number of Connected Components in an Undirected Graph
694. Number of Distinct Islands
695. Max Area of Island
1020. Number of Enclaves
1254. Number of Closed Islands
1905. Count Sub Islands */

#include <vector>

using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;

        int result = 0;
        _RowSize = grid.size();
        _ColSize = grid[0].size();

        for (auto col = 0; col < _ColSize; ++col) {
            dfs(grid, 0, col);
            dfs(grid, _RowSize-1, col);
        }
        for (auto row = 0; row < _RowSize; ++row) {
            dfs(grid, row, 0);
            dfs(grid, row, _ColSize-1);
        }

        for (auto row = 0; row < _RowSize; ++row) {
            for (auto col = 0; col < _ColSize; ++col) {
                if (grid[row][col] == 1) {
                    ++result;
                }
            }
        }

        return result;
    }

private:
    void dfs(vector<vector<int>>& grid, int row, int col) {
        if (row < 0 || row >= _RowSize || col < 0 || col >= _ColSize)
            return;
        if (grid[row][col] == 0)
            return;

        grid[row][col] = 0;

        for (const auto& [r, c] : _Direction) {
            dfs(grid, row + r, col + c);
        }
    }

private:
    int _RowSize{0};
    int _ColSize{0};
    const vector<pair<int, int>> _Direction {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
    };
};