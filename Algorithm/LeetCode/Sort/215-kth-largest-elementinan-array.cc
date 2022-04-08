/* Easy
Find the kth largest element in an unsorted array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:
Input: [3,2,1,5,6,4] and k = 2
Output: 5

Example 2:
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4

Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.

Constraints:
1 <= k <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4

Relatives:
215. Kth Largest Element in an Array
324. Wiggle Sort II
347. Top K Frequent Elements
414. Third Maximum Number
703. Kth Largest Element in a Stream
973. K Closest Points to Origin
1985. Find the Kth Largest Integer in the Array */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>

using namespace std;

// STL Heap Sort Solution
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::priority_queue<int, vector<int>, std::greater<int>> minHeap;

        for (const auto& num : nums) {
            minHeap.emplace(num);
            if (minHeap.size() > k)
                minHeap.pop();
        }

        return minHeap.top();
    }
};

// Heap Sort Solution
class Solution {
public:
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

private:
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
};

// STL Build in Solution
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        nth_element(nums.begin(), nums.end() - k, nums.end());
        return nums[len - k];
    }
};

// Qiuck Sort Solution
class Solution {
public:
    int findKthLargest_qsort(vector<int> &nums, int k) {
        int len = nums.size(), pos;
        int left = 0, right = len - 1;
        while (left <= right) {
            pos = partition(nums, left, right);
            if (pos == k - 1)
                return nums[pos];
            else if (pos < k - 1)
                left = pos + 1;
            else
                right = pos - 1;
        }

        return 0;
    }

private:
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
};

// TODO: not work
class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        quickSelectK(nums, 0, nums.size()-1, k-1);

        return nums[k-1];
    }

private:
    void quickSelectK(vector<int>& nums, int beg, int end, int k) {
        while (beg < end) {
            auto pivot = partition(nums, beg, end);
            if (pivot < k)
                beg = pivot;
            else if (pivot > k)
                end = pivot - 1;
            else
                return;
        }
    }

    int partition(vector<int> &nums, int beg, int end) {
        auto pivot = nums[(beg + end) / 2];

        while (beg <= end) {
            while (nums[beg] > pivot)
                ++beg;
            while (nums[end] < pivot)
                --end;
            if (beg <= end)
                swap(nums[beg++], nums[end--]);
        }

        return beg;
    }
};