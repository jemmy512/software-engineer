/*
Difficulty: Easy

Find the kth largest element in an unsorted array. Note that it is the kth largest
 element in the sorted order, not the kth distinct element.

Example 1:
    Input: [3,2,1,5,6,4] and k = 2
    Output: 5

Example 2:
    Input: [3,2,3,1,2,4,5,5,6] and k = 4
    Output: 4
Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/
#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;

/******************************* Heap Sort Solution ***************************/
// 32 test cases, 10ms, beat 98.72%
void heapifyDown(vector<int> &nums, int b, int e) {
    for (int i = 2 * b + 1; i < e; i = 2 * i + 1) {
        if (i + 1 < e && nums[i + 1] < nums[i])
            ++i;
        if (nums[b] <= nums[i])
            break;
        swap(nums[b], nums[i]);
        b = i;
    }
}

int findKthLargest(vector<int>& nums, int k) {
    for (int i = k/2-1; i >=0; --i)
        heapifyDown(nums, i, k);

    for (int i = k; i < nums.size(); ++i) {
        if (nums[i] > nums[0]) {
            swap(nums[i], nums[0]);
            heapifyDown(nums, 0, k);
        }
    }

    return nums[0];
}

/******************************* STL Build in Solution ************************/
// 32 test cases, 10ms, beat 98.72%
int findKthLargest_buildin(vector<int>& nums, int k) {
    int len = nums.size();
    nth_element(nums.begin(), nums.end() - k, nums.end());
    return nums[len - k];
}

/******************************* Qiuck Sort Solution **************************/
// 32 test cases, 74ms, beat 13.94%
int partition(vector<int> &nums, int left, int right) {
    int pivot = nums[left];
    int l = left + 1, r = right;
    while (l <= r) {
        if (nums[l] < pivot && nums[r] > pivot)
            swap(nums[l], nums[r]);
        if (nums[l] >= pivot) ++l;
        if (nums[r] <= pivot) --r;
    }
    swap(nums[left], nums[r]);
    return r;
}

int findKthLargest_qsort(vector<int> &nums) {
    int len = nums.size(), pos;
    int left = 0, right = len - 1;
    while (true) {
        pos = partition(nums, left, right);
        if (pos == k - 1)
            return nums[pos];
        else if (pos < k - 1)
            left = pos + 1;
        else
            right = pos - 1;
    }
}

int main() {
    vector<int> nums = {3,2,5,8,4,7,6,9};
    findKthLargest(nums, 4);
    copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, " "));
}