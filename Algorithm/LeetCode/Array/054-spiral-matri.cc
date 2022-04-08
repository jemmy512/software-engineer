/* Medium
Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]


Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty())
            return {};

        const auto RowSize = matrix.size();
        const auto ColSize = matrix[0].size();
        const auto Size = RowSize * ColSize;
        int left = 0, top = 0;
        int right = ColSize - 1, bottom = RowSize - 1;

        vector<int> result;
        result.reserve(Size);

        while (result.size() < Size) {
            if (top <= bottom) {
                for (auto i = left; i <= right; ++i) {
                    result.push_back(matrix[top][i]);
                }
                ++top;
            }

            if (left <= right) {
                for (auto i = top; i <= bottom; ++i) {
                    result.push_back(matrix[i][right]);
                }
                --right;
            }

            if (top <= bottom) {
                for (auto i = right; i >= left; --i) {
                    result.push_back(matrix[bottom][i]);
                }
                --bottom;
            }

            if (left <= right) {
                for (auto i = bottom; i >= top; --i) {
                    result.push_back(matrix[i][left]);
                }
                ++left;
            }
        }

        return result;
    }
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty())
            return {};

        _RowSize = matrix.size();
        _ColSize = matrix[0].size();

        vector<int> result;
        result.reserve(_RowSize * _ColSize);

        for (int row = 0, col = 0; row < (_RowSize+1)/2 && col < (_ColSize+1)/2; ++row, ++col) {
            for (int i = col; i < _ColSize-col; ++i)
                result.emplace_back(matrix[row][i]);

            for (int i = row+1; i < _RowSize-row; ++i)
                result.emplace_back(matrix[i][_ColSize-col-1]);

            for (int i = _ColSize-col-2; _RowSize-row-1 > row && i >= col; --i)
                result.emplace_back(matrix[_RowSize-row-1][i]);

            for (int i = _RowSize-row-2; _ColSize-col-1 > col && i > row; --i)
                result.emplace_back(matrix[i][col]);
        }

        return result;
    }

private:
    int _RowSize{0};
    int _ColSize{0};
};