/* Medium
You are given an size x size 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
Example 3:

Input: matrix = [[1]]
Output: [[1]]
Example 4:

Input: matrix = [[1,2],[3,4]]
Output: [[3,1],[4,2]]


Constraints:
matrix.length == size
matrix[i].length == size
1 <= size <= 20
-1000 <= matrix[i][j] <= 1000

Relatives:
048. Rotate Image
054. Spiral Matrix
059. Spiral Matrix II */

#include <vector>

using namespace std;

/*
- x - - - [i, j]
- - - - x [j, n-1-i]
- - - - -
x - - - - [n-1-j, i]
- - - x - [n-1-i, n-1-j]
*/

// 1. rotate 90 degree clockwise
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        roateDiagnoal(matrix);
        rotateVertical(matrix);
    }

private:
    // left top / right bottom diagnoal roate
    void roateDiagnoal(vector<vector<int>>& matrix) {
        const auto size = matrix.size();

        for (auto r = 0; r < size; ++r) {
            for (auto c = r; c < size; ++c) {
                swap(matrix[r][c], matrix[c][r]);
            }
        }
    }

    void rotateVertical(vector<vector<int>>& matrix) {
        const auto size = matrix.size();

        for (auto r = 0; r < size; ++r) {
            auto b = 0;
            auto e = size - 1;
            while (b < e) {
                swap(matrix[r][b++], matrix[r][e--]);
            }
        }
    }
};

// 2. rotate 90 degree anticlockwise
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        roateDiagnoal(matrix);
        rotateVertical(matrix);
    }

private:
    // left bottom / right top diagnoal roate
    void roateDiagnoal(vector<vector<int>>& matrix) {
        const auto size = matrix.size();

        for (auto r = 0; r < size; ++r) {
            for (auto c = 0; c < size - r; ++c) {
                swap(matrix[r][c], matrix[size-c-1][size-r-1]);
            }
        }
    }

    void rotateVertical(vector<vector<int>>& matrix) {
        const auto size = matrix.size();

        for (auto r = 0; r < size; ++r) {
            auto b = 0;
            auto e = size - 1;
            while (b < e) {
                swap(matrix[r][b++], matrix[r][e--]);
            }
        }
    }
};

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        const auto size = matrix.size();
        // for (int i = 0; i < (size + 1) / 2; i++) {
        for (int i = 0; i < (size / 2 + size % 2); i++) {
            for (int j = 0; j < size / 2; j++) {
                int temp = matrix[size - 1 - j][i];
                matrix[size - 1 - j][i] = matrix[size - 1 - i][size - 1 - j];
                matrix[size - 1 - i][size - 1 - j] = matrix[j][size - 1 - i];
                matrix[j][size - 1 - i] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }
    }
};