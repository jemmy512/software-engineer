/* Hard
Given a rows x cols binary matrix filled with 0's and 1's,
find the largest rectangle containing only 1's and return its area.

Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = [["0"]]
Output: 0

Example 3:
Input: matrix = [["1"]]
Output: 1

Constraints:
rows == matrix.length
cols == matrix[r].length
1 <= row, cols <= 200
matrix[r][c] is '0' or '1'.

Relatives:
084. Largest Rectangle in Histogram
085. Maximal Rectangle
221. Maximal Square */

#include <vector>

using namespace std;

// Time complexity: O(NM)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int RowSize = matrix.size();
        int ColSize = matrix[0].size();

        int maxArea = 0;
        auto left = vector<int>(ColSize, 0); // initialize left as the leftmost boundary possible
        auto right = vector<int>(ColSize, ColSize); // initialize right as the rightmost boundary possible
        auto height = vector<int>(ColSize, 0);

        for (auto i = 0; i < RowSize; ++i) {
            int curLeft = 0, curRight = ColSize;

            for (auto j = 0; j < ColSize; ++j) {
                if (matrix[i][j] == '1')
                    height[j]++;
                else
                    height[j] = 0;
            }

            for (auto j = 0; j < ColSize; ++j) {
                if (matrix[i][j] == '1') {
                    left[j] = max(left[j], curLeft);
                } else {
                    left[j] = 0;
                    curLeft = j + 1;
                }
            }

            for (int j = ColSize - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    right[j] = min(right[j], curRight);
                } else {
                    right[j] = ColSize;
                    curRight = j;
                }
            }

            for (auto j = 0; j < ColSize; ++j) {
                maxArea = max(maxArea, (right[j] - left[j]) * height[j]);
            }
        }

        return maxArea;
    }
};

// Time complexity: O(MMN)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        auto RowSize = matrix.size();
        auto ColSize = matrix[0].size();

        // dp[r][c] : max len of all 1s ends with col c at row r.
        vector<vector<int>> dp(RowSize, vector(ColSize, 0));

        for (auto r = 0; r < RowSize; ++r) {
            for (auto c = 0; c < ColSize; ++c) {
                dp[r][c] = (matrix[r][c] == '1') ? (c == 0 ? 1 : dp[r][c - 1] + 1) : 0;
            }
        }

        int ret = 0;

        for (auto r = 0; r < RowSize; ++r) {
            for (auto c = 0; c < ColSize; ++c) {
                auto width = INT_MAX;
                for (auto k = r; k < RowSize; ++k) {
                    if (width = min(width, dp[k][c])) {
                        auto height = k - r + 1;
                        ret = max(width * height , ret);
                    } else {
                        break;
                    }
                }
            }
        }

        return ret;
    }
};