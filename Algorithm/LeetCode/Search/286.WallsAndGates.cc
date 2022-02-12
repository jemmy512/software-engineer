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

Constraints:

m == rooms.length
n == rooms[i].length
1 <= m, n <= 250
rooms[i][j] is -1, 0, or 2^31 - 1.

Relatives:
130. Surrounded Regions
200. Number of Islands
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
        if (rooms.empty())
            return;

        _RowSize = rooms.size();
        _ColSize = rooms[0].size();

        queue<pair<int, int>> que;

        for (auto row = 0; row < _RowSize; ++row) {
            for (auto col = 0; col < _ColSize; ++col) {
                if (rooms[row][col] == Gate) {
                    que.emplace(row, col);
                }
            }
        }

        while (!que.empty()) {
            // ERROR: AddressSanitizer: heap-use-after-free on address 0x615000004878
            // const auto& [row, col] = que.front();
            const auto [row, col] = que.front();
            que.pop();

            for (const auto& [r, c] : _Directions) {
                const auto rowNew = row + r;
                const auto colNew = col + c;

                if (isValid(rooms, rowNew, colNew)) {
                    rooms[rowNew][colNew] = rooms[row][col] + 1;
                    que.emplace(rowNew, colNew);
                }
            }
        }
    }

private:
    bool isValid(const vector<vector<int>>& rooms, int row, int col) {
        return (row >= 0 && row < _RowSize && col >= 0 && col < _ColSize && rooms[row][col] == Empty);
    }

private:
    int _RowSize{0};
    int _ColSize{0};
    const vector<pair<int, int>> _Directions {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    // non-static data member cannot be constexpr
    static constexpr auto Gate = 0;
    static constexpr auto Empty = 2147483647;
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