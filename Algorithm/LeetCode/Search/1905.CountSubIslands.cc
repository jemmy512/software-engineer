/* Medium
You are given two m x n binary matrices grid1 and grid2
containing only 0's (representing water) and 1's (representing land).
An island is a group of 1's connected 4-directionally (horizontal or vertical).
Any cells outside of the grid are considered water cells.

An island in grid2 is considered a sub-island if there is an island in grid1
that contains all the cells that make up this island in grid2.

Return the number of islands in grid2 that are considered sub-islands.

Example 1:
Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]],
grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
Output: 3
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.

Example 2:
Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]],
grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
Output: 2
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are two sub-islands.

Constraints:
m == grid1.length == grid2.length
n == grid1[i].length == grid2[i].length
1 <= m, n <= 500
grid1[i][j] and grid2[i][j] are either 0 or 1.

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
    int countSubIslands(vector<vector<int>>& src, vector<vector<int>>& tar) {
        int result = 0;
        RowSize = src.size();
        ColSize = src[0].size();

        for (auto row = 0; row < RowSize; ++row) {
            for (auto col = 0; col < ColSize; ++col) {
                if (tar[row][col] == 1 && src[row][col] == 0) {
                    dfs(tar, row, col);
                }
            }
        }

        for (auto row = 0; row < RowSize; ++row) {
            for (auto col = 0; col < ColSize; ++col) {
                if (tar[row][col] == 1) {
                    ++result;
                    dfs(tar, row, col);
                }
            }
        }

        return result;
    }

private:
    void dfs(vector<vector<int>>& grid, int row, int col) {
        if (row < 0 || row >= RowSize || col < 0 || col >= ColSize)
            return;
        if (grid[row][col] == 0)
            return;

        grid[row][col] = 0;

        for (const auto& [r, c] : Directions) {
            dfs(grid, row + r, col + c);
        }
    }

private:
    int RowSize{0};
    int ColSize{0};
    const vector<pair<int, int>> Directions {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };
};