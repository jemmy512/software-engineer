/* Hard
The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon.
The dungeon consists of m x n rooms laid out in a 2D grid.
Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer.
If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers),
so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0)
or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Return the knight's minimum initial health so that he can rescue the princess.

Note that any room can contain threats or power-ups, even the first room the knight enters
and the bottom-right room where the princess is imprisoned.

Example 1:
Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.

Example 2:
Input: dungeon = [[0]]
Output: 1

Constraints:
m == dungeon.length
n == dungeon[i].length
1 <= m, n <= 200
-1000 <= dungeon[i][j] <= 1000

The key point is not to eat the most blood vials, but to lose the least amount of health */

#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        RowSize = dungeon.size();
        ColSize = dungeon[0].size();
        Memo = vector(RowSize, vector(ColSize, -1));

        return dp(dungeon, 0, 0);
    }

private:
    // returns the minimal health from [row, col] to the bottom-right cornel
    int dp(const vector<vector<int>>& dungeon, int row, int col) {
        if (row == RowSize - 1 && col == ColSize - 1)
            return dungeon[row][col] >= 0 ? 1 : -dungeon[row][col] + 1;

        if (row == RowSize || col == ColSize)
            return INT_MAX;

        if (Memo[row][col] != -1)
            return Memo[row][col];

        auto ret = min(dp(dungeon, row + 1, col), dp(dungeon, row, col + 1)) - dungeon[row][col];
        Memo[row][col] = ret <= 0 ? 1 : ret;

        return Memo[row][col];
    }

private:
    int RowSize{0};
    int ColSize{0};
    vector<vector<int>> Memo;
};