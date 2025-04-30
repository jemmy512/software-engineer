/* Medium
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells,
where adjacent cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.

Example 1:
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []


Constraints:
m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 10^4
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.

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
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty())
            return {};

        vector<string> result;
        _RowSize = board.size();
        _ColSize = board[0].size();
        vector<bool> visitedWord(words.size(), false);

        for (int row = 0; row < _RowSize; ++row) {
            for (int col = 0; col < _ColSize; ++col) {
                for (int i = 0; i < words.size(); ++i) {
                    if (!visitedWord[i] && backtrack(board, words[i], row, col, 0)) {
                        visitedWord[i] = true;
                        result.emplace_back(words[i]);
                    }
                }
            }
        }

        return result;
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

    bool isBoundary(int row, int col) {
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

/* visitedWord can handle this case:
[["a","a"]]
["a"]
*/