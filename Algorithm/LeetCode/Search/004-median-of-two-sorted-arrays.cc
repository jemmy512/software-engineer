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

// O(logN) approch : binary search for partition
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) {
            swap(a, b);
        }

        const auto sizeA = a.size();
        const auto sizeB = b.size();
        const auto halfSize = (sizeA + sizeB + 1) / 2;
        const auto isOdd = (sizeA + sizeB) % 2 == 1;
        int beg = 0;
        int end = sizeA;

        while (beg <= end) {
            int posA = (beg + end) / 2;
            int posB = halfSize - posA;

            int leftAmax = (posA == 0) ? INT_MIN : a[posA-1];
            int rightAmin = (posA == sizeA) ? INT_MAX : a[posA];

            int leftBmax = (posB == 0) ? INT_MIN : b[posB-1];
            int rightBmin = (posB == sizeB) ? INT_MAX : b[posB];

            if (leftAmax <= rightBmin && leftBmax <= rightAmin) {
                if (isOdd)
                    return double(max(leftAmax, leftBmax));
                else
                    return double(max(leftAmax, leftBmax) + min(rightAmin, rightBmin))/2;
            } else if (leftAmax > rightBmin) {
                end = posA-1;
            } else {
                beg = posA+1;
            }
        }

        return 0;
    }
};