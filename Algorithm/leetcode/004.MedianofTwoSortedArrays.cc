/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/
#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;

// 71ms, beat 66.45%
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    if (m > n) return findMedianSortedArrays(nums2, nums1);
    int i, j, imin = 0, imax = m, half = (m + n + 1) / 2;
    while (imin <= imax) {
        i = (imin & imax) + ((imin ^ imax) >> 1);
        j = half - i;
        if (i > 0 && j < n && nums1[i - 1] > nums2[j]) imax = i - 1;
        else if (j > 0 && i < m && nums2[j - 1] > nums1[i]) imin = i + 1;
        else break;
    }
    int num1;
    if (!i) num1 = nums2[j - 1];
    else if (!j) num1 = nums1[i - 1]; 
    else num1 = max(nums1[i - 1], nums2[j - 1]);
    if ((m + n) & 1) return num1;
    int num2;
    if (i == m) num2 = nums2[j];
    else if (j == n) num2 = nums1[i];
    else num2 = min(nums1[i], nums2[j]);
    return (num1 + num2) / 2.0;
}

// 89ms, beat 17.00%
double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
    int i = 0;
    int j = 0;
    double ret;
    int len1 = nums1.size();
    int len2 = nums2.size();
    
    vector<int> vec;
    while (i < len1 && j < len2) {
        if (nums1[i] < nums2[j]) {
            vec.push_back(nums1[i++]);
        } else {
            vec.push_back(nums2[j++]);
        }
    }
    while (i < len1)
        vec.push_back(nums1[i++]);
    while (j < len2)
        vec.push_back(nums2[j++]);
    
    int len = vec.size();
    if (len % 2)
        return (double)vec[len / 2];
    else 
        return (vec[len / 2] + vec[len / 2 - 1] + 0.0) / 2;
}

int main() {
    vector<int> vec = {1, 2};
    vector<int> ve = {3, 4, 5, 6};
    cout << findMedianSortedArrays(vec, ve) << endl;
}
