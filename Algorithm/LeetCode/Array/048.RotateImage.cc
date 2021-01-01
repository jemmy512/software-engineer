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
-1000 <= matrix[i][j] <= 1000 */

#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int size = matrix.size();
        for (int i = 0; i < (size + 1) / 2; i++) {
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