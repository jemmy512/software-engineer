/* Easy
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold
additional elements from nums2. The number of elements initialized in nums1 and nums2 are
m and n respectively.

Example:
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
Output: [1,2,2,3,5,6]

Constraints:
-10^9 <= nums1[i], nums2[i] <= 10^9
nums1.length == m + n
nums2.length == n

Relatives:
021. Merge Two Sorted List
023. Merge k Sorted Lists
088. Merge Sorted Array
148. Sort List
244. Shortest Word Distance II
1634. Add Two Polynomials Represented as Linked Lists */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/* Two pointers / Start from the end */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    nums1.resize(m + n);
    int i = m - 1, j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        nums1[k--] = (nums1[i] > nums2[j]) ? nums1[i--] : nums2[j--];
    }

    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

/* Two pointers / Start from the begining */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> tmp(m + n);
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < m && j < n) {
        if (nums1[i] < nums2[j])
            tmp[k++] = nums1[i++];
        else if (nums1[i] > nums2[j])
            tmp[k++] = nums2[j++];
        else {
            tmp[k++] = nums1[i];
            ++i; ++j;
        }
        // not care about repeat
        // tmp[k++] = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
    }
    while (i < m)
        tmp[k++] = nums1[i++];
    while (j < n)
        tmp[k++] = nums2[j++];
    nums1.clear();
    copy(tmp.begin(), tmp.end(), back_inserter(nums1));
}

int main() {
    vector<int> vec1(12);
    vec1 = {1, 3, 5, 7, 9};
    cout << vec1.capacity() << endl;
    vector<int> vec2 = {2, 4 ,6, 8, 10};
    merge(vec1, vec1.size(), vec2, vec2.size());
    for_each(vec1.begin(), vec1.end(), [](const int &n) {
        cout << n << " ";
    });
    cout << endl;
}