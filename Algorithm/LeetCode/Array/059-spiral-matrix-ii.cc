/* Medium
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.

Example 1:
Input: n = 3
Output: [[1,2,3],[8,9,4],[7,6,5]]

Example 2:
Input: n = 1
Output: [[1]]

Constraints:
1 <= n <= 20 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int size) {
        vector<vector<int>> matrix(size, vector(size, 0));

        int cnt = 1;
        int left = 0, top = 0;
        int right = size - 1, bottom = size - 1;

        while (cnt <= size * size) {
            if (top <= bottom) {
                for (auto i = left; i <= right; ++i) {
                    matrix[top][i] = cnt++;
                }
                ++top;
            }

            if (left <= right) {
                for (auto i = top; i <= bottom; ++i) {
                    matrix[i][right] = cnt++;
                }
                --right;
            }

            if (top <= bottom) {
                for (auto i = right; i >= left; --i) {
                    matrix[bottom][i] = cnt++;
                }
                --bottom;
            }

            if (left <= right) {
                for (auto i = bottom; i >= top; --i) {
                    matrix[i][left] = cnt++;
                }
                ++left;
            }
        }

        return matrix;
    }
};