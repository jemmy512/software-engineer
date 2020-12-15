/* Medium
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by
its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1)
and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.

Relatives:
303. Range Sum Query Immutable
307. Range Sum Query Mutable
304. Range Sum Query 2D Immutable */

#include <iostream>
#include <vector>

using namespace std;


/* Construct a 2D array `sums[row+1][col+1]`
 *
 * (**notice**: we add additional blank row `sums[0][col+1]={0}` and blank column `sums[row+1][0]={0}`
 * to remove the edge case checking), so, we can have the following definition
 *
 *  `sums[i+1][j+1]` represents the sum of area from `matrix[0][0]` to `matrix[i][j]`
 *
 * To calculate sums, the ideas as below
 *
 *     +-----+-+-------+     +--------+-----+     +-----+---------+     +-----+--------+
 *     |     | |       |     |        |     |     |     |         |     |     |        |
 *     |     | |       |     |        |     |     |     |         |     |     |        |
 *     +-----+-+       |     +--------+     |     |     |         |     +-----+        |
 *     |     | |       |  =  |              |  +  |     |         |  -  |              |
 *     +-----+-+       |     |              |     +-----+         |     |              |
 *     |               |     |              |     |               |     |              |
 *     |               |     |              |     |               |     |              |
 *     +---------------+     +--------------+     +---------------+     +--------------+
 *
 *        sums[i][j]      =    sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]   +
 *
 *                             matrix[i-1][j-1]
 *
 * So, we use the same idea to find the specific area's sum.
 *
 *     +---------------+   +--------------+   +---------------+   +--------------+   +--------------+
 *     |               |   |         |    |   |   |           |   |         |    |   |   |          |
 *     |   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
 *     |   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
 *     |   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
 *     |   |      |    |   |         |    |   |   |           |   |              |   |              |
 *     |   +------+    |   +---------+    |   +---+           |   |              |   |              |
 *     |        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
 *     +---------------+   +--------------+   +---------------+   +--------------+   +--------------+ */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.empty() || matrix[0].empty())
            return;

        int rowSize = matrix.size() + 1;
        int colSize = matrix[0].size() + 1;
        data = vector<vector<int>>(rowSize, vector<int>(colSize, 0));

        for (int row = 1; row < rowSize; ++row) {
            for (int col = 1; col < colSize; ++col) {
                data[row][col] = data[row][col-1] + data[row-1][col] + matrix[row-1][col-1] - data[row-1][col-1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return data[row2+1][col2+1] - data[row2+1][col1] - data[row1][col2+1] + data[row1][col1];
    }

private:
    vector<vector<int>> data;
};

/* Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2); */
