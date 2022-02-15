/* Hard
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement,
where 'Q' and '.' both indicate a queen and an empty space, respectively.

Example 1:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:
Input: n = 1
Output: [["Q"]]

Constraints:
1 <= n <= 9 */

#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        Col = vector(N, false);
        DiagonalLeft = DiagonalRight = vector(2 * N - 1, false);

        auto board = vector<string>(n, string(n, '.'));
        backtrack(board, 0);

        return Queens;
    }

private:
    void backtrack(vector<string>& board, int row) {
        if (row == N) {
            Queens.push_back(board);
        } else {
            for (auto col = 0; col < N; ++col) {
                if (isValid(board, row, col))  {
                    board[row][col] = 'Q';
                    Col[col] = DiagonalLeft[row + col] = DiagonalRight[row - col + N - 1] = true;

                    backtrack(board, row + 1);

                    board[row][col] = '.';
                    Col[col] = DiagonalLeft[row + col] = DiagonalRight[row - col + N - 1] = false;
                }
            }
        }
    }

    bool isValid(const vector<string>& board, int row, int col) {
        if (Col[col])
            return false;

        if (DiagonalLeft[row + col] || DiagonalRight[row - col + N - 1])
            return false;

        return true;
    }

private:
    int N{0};
    vector<bool> Col;           // no attack on column
    vector<bool> DiagonalLeft;  // no attack on left diagonal
    vector<bool> DiagonalRight; // no attack on right diagonal
    vector<vector<string>> Queens;
};

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        auto board = vector<string>(n, string(n, '.'));
        backtrack(board, 0);

        return Queens;
    }

private:
    void backtrack(vector<string>& board, int row) {
        if (row == N) {
            Queens.push_back(board);
        } else {
            for (auto col = 0; col < N; ++col) {
                if (isValid(board, row, col))  {
                    board[row][col] = 'Q';
                    backtrack(board, row + 1);
                    board[row][col] = '.';
                }
            }
        }
    }

    bool isValid(const vector<string>& board, int row, int col) {
        for (auto i = 0; i < N; ++i) {
            if (board[i][col] == 'Q')
                return false;
        }

        for (int i = row-1, j = col-1; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q')
                return false;
        }

        for (int i = row-1, j = col+1; i >= 0 && j < N; --i, ++j) {
            if (board[i][j] == 'Q')
                return false;
        }

        return true;
    }

private:
    int N {0};
    vector<vector<string>> Queens;
};