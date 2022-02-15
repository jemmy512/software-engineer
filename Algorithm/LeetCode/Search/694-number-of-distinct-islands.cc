/* Medium
You are given an m x n binary matrix grid.
An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.

An island is considered to be the same as another if and only if one island can be translated
(and not rotated or reflected) to equal the other.

Return the number of distinct islands.

Example 1:
Input: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
Output: 1

Example 2:
Input: grid = [[1,1,0,1,1],[1,0,0,0,0],[0,0,0,0,1],[1,1,0,1,1]]
Output: 3

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 50
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
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        RowSize = grid.size();
        ColSize = grid[0].size();

        for (auto row = 0; row < RowSize; ++row) {
            for (auto col = 0; col < ColSize; ++col) {
                if (grid[row][col] == 1) {
                    std::string path;
                    dfs(grid, row, col, path, 0);
                    Set.emplace(std::move(path));
                }
            }
        }

        return Set.size();
    }

private:
    void dfs(vector<vector<int>>& grid, int row, int col, std::string& path, int dir) {
        if (row < 0 || row >= RowSize || col < 0 || col >= ColSize)
            return;
        if (grid[row][col] == 0)
            return;

        grid[row][col] = 0;
        path += std::to_string(dir);

        for (const auto& d : Directions) {
            dfs(grid, row + d[0], col + d[1], path, d[2]);
        }

        path += std::to_string(-dir);
    }

private:
    set<std::string> Set;
    int RowSize{0};
    int ColSize{0};
    const vector<vector<int>> Directions {
        {0, 1, 1}, // row, col, direction code
        {0, -1, 2},
        {1, 0, 3},
        {-1, 0, 4}
    };
};