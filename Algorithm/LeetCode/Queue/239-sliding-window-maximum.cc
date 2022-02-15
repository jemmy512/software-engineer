/* Hard
Given an array nums, there is a sliding window of size k which is moving from the very
left of the array to the very right. You can only see the k numbers in the window.
Each time the sliding window moves right by one position. Return the max sliding window.

Follow up:
Could you solve it in linear time?

Example:
Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7]
Explanation:

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7


Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length

Relatives:
076. Minimum Window Substring
155. Min Stack
239. Sliding Window Maximum
1696. Jump Game VI

123. Best Time to Buy and Sell Stock III
238. Product of Array Except Self */

#include <vector>
#include <deque>

using namespace std;

/* dp solution
 * Time complexity: O(N), since all we do is 3 passes along the array of length N.
 * Space complexity: O(N) to keep left and right arrays of length N, and output array of length N - k + 1.*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.size() * k == 0)
            return {};
        if (k == 1)
            return nums;

        const auto size = nums.size();
        vector<int> left(size, nums[0]);
        vector<int> right(size, nums[size-1]);
        vector<int> result(size-k+1);

        for (auto i = 1; i < size; ++i) {
            left[i] = (i % k == 0) ? nums[i] : max(left[i-1], nums[i]);

            auto j = size - i - 1;
            right[j] = ((j+1) % k == 0) ? nums[j] : max(right[j+1], nums[j]);
        }

        for (auto i = 0; i < size-k+1; ++i) {
            result[i] = max(left[i+k-1], right[i]);
        }

        return result;
    }
};

/* deque solution
 * Time complexity: O(N), since each element is processed exactly twice - it's index added and then removed from the deque.
 * Space complexity: O(N), since O(N−k+1) is used for an output array and O(k) for a deque. */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.size() < k)
            return {};

        deque<int> dque;
        vector<int> window;
        window.reserve(nums.size()-k+1);

        for (int i = 0; i < nums.size(); ++i) {
            // pop the most left ele which will leave the window
            if (!dque.empty() && dque.front() == i - k)
                dque.pop_front();

            // pop all eles less than current ele
            while (!dque.empty() && nums[i] > nums[dque.back()])
                dque.pop_back();

            dque.emplace_back(i);

            if (i >= k - 1)
                window.emplace_back(nums[dque.front()]);
        }

        return window;
    }
};