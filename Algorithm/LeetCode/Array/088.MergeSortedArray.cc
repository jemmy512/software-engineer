/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold 
additional elements from nums2. The number of elements initialized in nums1 and nums2 are
 m and n respectively.
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

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
    for_each(vec1.begin(), vec1.end(), [](const int &n){
        cout << n << " ";
    });
    cout << endl;
}