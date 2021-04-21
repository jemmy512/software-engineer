/* Hard
Given two sorted arrays nums1 and nums2 of size m and n respectively,
return the median of the two sorted arrays.

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Example 3:
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000

Example 4:
Input: nums1 = [], nums2 = [1]
Output: 1.00000

Example 5:
Input: nums1 = [2], nums2 = []
Output: 2.00000

Constraints:
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6 */

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    // O(logN) approch : binary search for partition
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) {
            swap(a, b);
        }

        int x = a.size();
        int y = b.size();
        int low = 0;
        int high = x;

        while (low <= high) {
            int px = (low + high) / 2;
            int py = (x + y + 1) / 2 - px;

            int maxleftx = (px == 0) ? INT_MIN : a[px-1];
            int minrightx = (px == x) ? INT_MAX : a[px];

            int maxlefty = (py == 0) ? INT_MIN : b[py-1];
            int minrighty = (py == y) ? INT_MAX : b[py];

            if (maxleftx <= minrighty && maxlefty <= minrightx) {
                if ((x+y)%2)
                    return double(max(maxleftx, maxlefty));
                else
                    return double(max(maxleftx, maxlefty) + min(minrightx, minrighty))/2;
            } else if (maxleftx > minrighty) {
                high = px-1;
            } else {
                low = px+1;
            }
        }

        return 0;
    }

    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();
        if (m > n) { // to ensure m<=n
            std::swap(A, B);
            std::swap(m, n);
        }

        int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;

        while (iMin <= iMax) {
            int i = (iMin + iMax) / 2;
            int j = halfLen - i;

            if (i < iMax && B[j-1] > A[i]){
                iMin = i + 1;       // i is too small
            } else if (i > iMin && A[i-1] > B[j]) {
                iMax = i - 1;       // i is too big
            } else {                // i is perfect
                int maxLeft = 0;
                if (i == 0) {
                    maxLeft = B[j-1];
                } else if (j == 0) {
                    maxLeft = A[i-1];
                } else {
                    maxLeft = max(A[i-1], B[j-1]);
                }

                if ((m + n) % 2 == 1) {
                    return maxLeft;
                }

                int minRight = 0;
                if (i == m) {
                    minRight = B[j];
                } else if (j == n) {
                    minRight = A[i];
                } else {
                    minRight = min(B[j], A[i]);
                }

                return (maxLeft + minRight) / 2.0;
            }
        }

        return 0.0;
    }
};