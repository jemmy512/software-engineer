/* Medium
Given an m x n 2d grid map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally
or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.

Relatives:
130.Surrounded Regions
200.Number of Islands
286. Walls and Gates
305. Number of Islands II
323. Number of Connected Components in an Undirected Graph
694. Number of Distinct Islands
695. Max Area of Island */

#include <vector>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rowSize = grid.size();
        int colSize = grid[0].size();
        int ret = 0;

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (grid[row][col] == '1') {
                    ++ret;
                    dfs(grid, row, col);
                }
            }
        }

        return ret;
    }

private:
    void dfs(vector<vector<char>>& grid, int row, int col) {
        int rowSize = grid.size();
        int colSize = grid[0].size();

        grid[row][col] = '0';
        if (row + 1 < rowSize && grid[row+1][col] == '1') dfs(grid, row+1, col);
        if (col + 1 < colSize && grid[row][col+1] == '1') dfs(grid, row, col+1);
        if (row - 1 >= 0 && grid[row-1][col] == '1') dfs(grid, row-1, col);
        if (col -1 >= 0 && grid[row][col-1] == '1') dfs(grid, row, col-1);
    }
};