/* Medium
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each r must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

Note:
A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example 1:
Input: board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true

Example 2:
Input: board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8.
Since there are two 8's in the top left 3x3 sub-box, it is invalid.


Constraints:
board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.

Relativeness:
036. Valid Sudoku
037. Sudoku Solver */

#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        constexpr int N = 9;
        int bitsRow[N] = { 0 };
        int bitsCol[N] = { 0 };
        int bitsSubBox[N] = { 0 };

        for (auto r = 0; r < N; ++r) {
            for (auto c = 0; c < N; ++c) {

                if (board[r][c] != '.') {
                    int num = board[r][c] - '0';
                    int bit = 1 << (num - 1);

                    // '>' has higher priority than '&'
                    if ((bitsRow[r] & bit) > 0)
                        return false;

                    if ((bitsCol[c] & bit) > 0)
                        return false;

                    int pos = r / 3 * 3 + c / 3;
                    if ((bitsSubBox[pos] & bit) > 0)
                        return false;

                    bitsRow[r] |= bit;
                    bitsCol[c] |= bit;
                    bitsSubBox[pos] |= bit;
                }
            }
        }

        return true;
    }
};