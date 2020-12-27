/* Medium
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 2^31 - 1 = 2147483647 to represent INF
as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate.
If it is impossible to reach a gate, it should be filled with INF.

Example:
Given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF

After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

Relatives:
130.Surrounded Regions
200.Number of Islands
286. Walls and Gates
305. Number of Islands II
323. Number of Connected Components in an Undirected Graph
694. Number of Distinct Islands
695. Max Area of Island */

#include <queue>
#include <vector>

using namespace std;

/* Instead of searching from an empty room to the gates,
 * how about searching the other way round?
 * In other words, we initiate breadth-first search (BFS) from all gates at the same time.
 * Since BFS guarantees that we search all rooms of distance d before searching rooms of distance d + 1,
 * the distance to an empty room must be the shortest */
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        _RowSize = rooms.size();
        if (_RowSize == 0)
            return;
        _ColSize = rooms[0].size();

        queue<pair<int, int>> que;
        for (int row = 0; row < _RowSize; ++row) {
            for (int col = 0; col < _ColSize; ++col) {
                if (rooms[row][col] == Gate) {
                    que.emplace(row, col);
                }
            }
        }

        while (!que.empty()) {
            int row = que.front().first;
            int col = que.front().second;
            que.pop();

            for (const auto& [r, c] : directions) {
                int rowNew = row + r;
                int colNew = col + c;
                if (isValidIndex(rooms, rowNew, colNew)) {
                    rooms[rowNew][colNew] = rooms[row][col] + 1;
                    que.emplace(rowNew, colNew);
                }
            }
        }
    }

private:
    bool isValidIndex(vector<vector<int>>& rooms, int row, int col) {
        return row >= 0 && col >= 0 && row < _RowSize && col < _ColSize && rooms[row][col] == Empty;
    }

private:
    int _RowSize{0};
    int _ColSize{0};
    const int Gate = 0;
    const int Empty = 2147483647;
    vector<pair<int, int>> directions{
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
};

int main() {
    vector<vector<int>> vec = {
        {2147483647,    -1,         0,          2147483647},
        {2147483647,    2147483647, 2147483647, -1},
        {2147483647,    -1,         2147483647, -1},
        {0,             -1,         2147483647, 2147483647}
    };

    Solution slution;
    slution.wallsAndGates(vec);
}