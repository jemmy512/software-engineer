/* Medium
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

Explanation:
Surrounded regions shouldn’t be on the border, which means that
any 'O' on the border of the board are not flipped to 'X'.
Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'.
Two cells are connected if they are adjacent cells connected horizontally or vertically.

Relatives:
130.Surrounded Regions
200.Number of Islands
286. Walls and Gates
305. Number of Islands II
323. Number of Connected Components in an Undirected Graph
694. Number of Distinct Islands
695. Max Area of Island */

#include <vector>
#include <unordered_map>

using namespace std;


/* This problem is almost identical as the capture rule of the
 * Go game https://en.wikipedia.org/wiki/Rules_of_Go#Capture,
 * where one captures the opponent's stones by surrounding them. */
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rowSize= board.size();
        if (rowSize <= 0)
            return;
        int colSize = board[0].size();

        for (int row = 0; row < rowSize; ++row) {
            dfs(board, row, 0);
            dfs(board, row, colSize-1);
        }
        for (int col = 0; col < colSize; ++col) {
            dfs(board, 0, col);
            dfs(board, rowSize-1, col);
        }

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (board[row][col] == 'O')
                    board[row][col] = 'X';
                if (board[row][col] == 'M')
                    board[row][col] = 'O';
            }
        }
    }

private:
    void dfs(vector<vector<char>>& board, int row, int col) {
        int rowSize= board.size();
        int colSize = board[0].size();

        if (row < 0 || col < 0 || row >= rowSize || col >= colSize)
            return;

        if (board[row][col] != 'O')
            return;

        board[row][col] = 'M';
        for (const auto& [r, c] : vector<pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
            dfs(board, row + r, col + c);
        }
    }
};

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rowSize = board.size();
        if (rowSize == 0) {
            return;
        }
        int colSize = board[0].size();

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (board[row][col] == 'O') {
                    dfs(board, row, col);
                }
            }
        }
    }

private:
    enum class Direction {
        Left,
        Right,
        Up,
        Down,
        All
    };

    bool dfs(vector<vector<char>>& board, int row, int col, Direction direction = Direction::All) {
        int rowSize = board.size();
        int colSize = board[0].size();
        bool ret = true;

        if (board[row][col] == 'O' && (row == 0 || col == 0 || row == rowSize-1 || col == colSize-1)) {
            return false;
        }

        if (board[row][col] == 'O') {
            board[row][col] = 'M';
            for (const auto& [dir, func] : dirFunction) {
                if (direction != dir)
                    ret = ret && func(board, row, col, dir);
            }
            board[row][col] = ret && direction == Direction::All ? 'X' : 'O';
        }

        return ret;
    }

    using Func = bool(vector<vector<char>>& board, int row, int col, Direction dir) ;
    std::function<Func> leftFunc = [this](vector<vector<char>>& board, int row, int col, Direction dir) {
        return dfs(board, row, col-1, Direction::Right);
    };
    std::function<Func> rightFunc = [this](vector<vector<char>>& board, int row, int col, Direction dir) {
        return dfs(board, row, col+1, Direction::Left);
    };
    std::function<Func> upFunc = [this](vector<vector<char>>& board, int row, int col, Direction dir) {
        return dfs(board, row-1, col, Direction::Down);
    };
    std::function<Func> downFunc = [this](vector<vector<char>>& board, int row, int col, Direction dir) {
        return dfs(board, row+1, col, Direction::Up);
    };

    unordered_map<Direction, std::function<Func>> dirFunction{
        {Direction::Left, leftFunc},
        {Direction::Right, rightFunc},
        {Direction::Up, upFunc},
        {Direction::Down, downFunc}
    };
};

int main() {
    vector<vector<char>> vec = {
        {'O','X','X','O','X'},
        {'X','O','O','X','O'},
        {'X','O','X','O','X'},
        {'O','X','O','O','O'},
        {'X','X','O','X','O'}
    };

    Solution solution;
    solution.solve(vec);
}