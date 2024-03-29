/* Medium
Given a n x n matrix where each of the rows and columns are sorted in ascending order,
find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.

Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 300
-10^9 <= matrix[i][j] <= 10^9
All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
1 <= k <= n^2

Follow up:
Could you solve the problem with a constant memory (i.e., O(1) memory complexity)?
Could you solve the problem in O(n) time complexity?
The solution may be too advanced for an interview but you may find reading this paper fun.

Relatives:
373. Find K Pairs with Smallest Sums
668. Kth Smallest Number in Multiplication Table
719. Find K-th Smallest Pair Distance
786. K-th Smallest Prime Fraction */

#include <vector>
#include <utility>

using namespace std;

/* binary search
 * Time complexity: O(Nlog(Max - Min))*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if (matrix.empty())
            return 0;

        rowSize = matrix.size();
        colSize = matrix[0].size();
        int start = matrix[0][0];
        int end = matrix[rowSize-1][colSize-1];

        while (start < end) {
            int mid = start + (end - start) / 2;
            auto leftRight = std::make_pair(matrix[0][0], matrix[rowSize-1][colSize-1]);
            int count = binarySearch(matrix, mid, leftRight);

            if (count == k) {
                return leftRight.first;
            } else if (count < k) {
                start = leftRight.second;
            } else {
                end = leftRight.first;
            }
        }

        return start;
    }

private:
    int binarySearch(vector<vector<int>>& matrix, int mid, std::pair<int, int>& leftRight) {
        int count = 0;
        int row = rowSize - 1;
        int col = 0;
        auto& [left, right] = leftRight;

        while (row >= 0 && col < colSize) {
            if (matrix[row][col] > mid) {
                right = min(right, matrix[row][col]);
                --row;
            } else {
                left = max(left, matrix[row][col]);
                count += row + 1;
                ++col;
            }
        }

        return count;
    }

private:
    int rowSize;
    int colSize;
};


/* heap sort, beat 5.24%
 * O(KN) */
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if (matrix.empty())
            return 0;

        auto rowSize = min((int)matrix.size(), k);
        auto colSize = matrix[0].size();
        vector<int> index(rowSize, 0);
        int result;

        while (k--) {
            int row = 0;
            while (index[row] >= colSize)
                ++row;
            result = matrix[row][index[row]];
            int idx = row++;

            while (row < index.size()) {
                if (index[row] < colSize && matrix[row][index[row]] < result) {
                    result = matrix[row][index[row]];
                    idx = row;
                }
                ++row;
            }
            ++index[idx];
        }

        return result;
    }
};