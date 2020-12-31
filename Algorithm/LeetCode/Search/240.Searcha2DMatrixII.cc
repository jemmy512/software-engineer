/* Medium
Write an efficient algorithm that searches for a target value in an
m x n integer matrix. The matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Example 1:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false

Constraints:
m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-10^9 <= matix[i][j] <= 10^9
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-10^9 <= target <= 10^9 */

#include <vector>
#include <utility>

using namespace std;

// binary search
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty())
            return false;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        int row = rowSize - 1;
        int col = 0; // also can search from top right corner

        while (row >= 0 && col < colSize) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] < target) {
                ++col;
            } else {
                --row;
            }
        }

        return false;
    }
};

// Doesn't work
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty())
            return false;

        rowSize = matrix.size();
        colSize = matrix[0].size();
        int start = matrix[0][0];
        int end = matrix[rowSize-1][colSize-1];

        while (start <= end) {
            int mid = start + (end - start) / 2;
            auto leftRight = std::make_pair(matrix[0][0], matrix[rowSize-1][colSize-1]);
            binarySearch(matrix, mid, leftRight);

            const auto& [left, right] = leftRight;

            if (target == left || target == right) {
                return true;
            } else if (target < left) {
                end = left;
            } else if (target > right) {
                start = right;
            } else {
                if (start == left && end == right) {
                    return false;
                } else {
                    start = left;
                    end = right;
                }
            }
        }

        return false;
    }

private:
    void binarySearch(vector<vector<int>>& matrix, int mid, std::pair<int, int>& leftRight) {
        int row = rowSize - 1;
        int col = 0;

        while (row >= 0 && col < colSize) {
            auto& [left, right] = leftRight;
            if (matrix[row][col] == mid) {
                left = right = mid;
                return;
            } else if (matrix[row][col] > mid) {
                right = min(right, matrix[row][col]);
                --row;
            } else {
                left = max(left, matrix[row][col]);
                ++col;
            }
        }
    }

private:
    int rowSize{0};
    int colSize{0};
};

/*
[[5],[6]]
6

[[-5]]
-2

[[-5]]
-5

[[-5]]
-10
*/