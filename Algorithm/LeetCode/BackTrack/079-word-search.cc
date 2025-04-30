/* Medium
Given an m x n board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells,
where "adjacent" cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once.

Example 1:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false


Constraints:
m == board.length
n = board[i].length
1 <= m, n <= 200
1 <= word.length <= 10^3
board and word consists only of lowercase and uppercase English letters.

Relatives:
079. Word Search
212. Word Search II
290. Word Pattern
291. Word Pattern II */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty())
            return false;

        _RowSize = board.size();
        _ColSize = board[0].size();

        for (int row = 0; row < _RowSize; ++row) {
            for (int col = 0; col < _ColSize; ++col) {
                if (backtrack(board, word, row, col, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    bool backtrack(vector<vector<char>>& board, const string& word, int row, int col, int index) {
        if (index == word.size())
            return true;

        if (isBoundary(row, col))
            return false;

        if (board[row][col] != word[index])
            return false;

        bool ret = false;
        board[row][col] = '#';

        for (const auto& [r, c] : directions) {
            if (backtrack(board, word, row + r, col + c, index + 1)) {
                ret = true;
                break;
            }
        }

        board[row][col] = word[index];

        return ret;
    }

    bool isBoundary(int row, int col) const {
        return (row < 0 || col < 0 || row >= _RowSize || col >= _ColSize);
    }

private:
    int _RowSize{0};
    int _ColSize{0};
    vector<std::pair<int, int>> directions {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };
};