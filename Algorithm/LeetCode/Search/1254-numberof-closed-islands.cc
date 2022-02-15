/* Medium
Given a 2D grid consists of 0s (land) and 1s (water).
An island is a maximal 4-directionally connected group of 0s
and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

Example 1:
Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation:
Islands in gray are closed because they are completely surrounded by water (group of 1s).

Example 2:
Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1
Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2

Constraints:
1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1

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
#include <utility>

using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;

        int result = 0;
        _RowSize = grid.size();
        _ColSize = grid[0].size();

        for (auto col = 0; col < _ColSize; ++col) {
            dfs(grid, 0, col);
            dfs(grid, _RowSize - 1, col);
        }

        for (auto row = 0; row < _RowSize; ++row) {
            dfs(grid, row, 0);
            dfs(grid, row, _ColSize - 1);
        }

        for (auto i = 0; i < _RowSize; ++i) {
            for (auto j = 0; j < _ColSize; ++j) {
                if (grid[i][j] == 0) {
                    ++result;
                    dfs(grid, i, j);
                }
            }
        }

        return result;
    }

private:
    void dfs(vector<vector<int>>& grid, int row, int col) {
        if (row < 0 || row >= _RowSize || col < 0 || col >= _ColSize)
            return;
        if (grid[row][col] == 1)
            return;

        grid[row][col] = 1;

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
        {1, 0},
        {-1, 0}
    };
};