/*Given an integer array nums, find the contiguous subarray (containing at least
 one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Follow up:

If you have figured out the O(n) solution, try coding another solution using the
 divide and conquer approach, which is more subtle.
*/

/* Ref: https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
 * Dynamic Solution
 * Time: O(N)
 * Space: O(1) */

// Kadane's_algorithm
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int curSum = nums[0];
        int beg = 0, end = nums.size();

        for (int i = 1; i < nums.size(); ++i) {
            if (curSum < 0) {
                beg = i;
                curSum = nums[i];
            } else {
                curSum += nums[i];
            }

            if (curSum > maxSum) {
                end = i;
                maxSum = curSum;
            }
        }

        cout << "[" << beg << ", " << end << "]" << endl;

        return maxSum;
    }
};
/*
    Divide and Conquer Solution
    Complexity:
        Time: O(NlogN)
        Space: O(1)
*/
class Solution {
public:
    int maxSub_divideConquer(vector<int> &nums, int beg, int end) {
        if (beg == end)
            return nums[beg];
        int mid = (beg + end) >> 1;
        int answer = max(maxSub_divideConquer(nums, beg, mid), maxSub_divideConquer(nums, mid + 1, end));
        int now = nums[mid], may = now;
        for (int i = mid - 1; i >= 0; --i)
            may = max(may, now += nums[i]);
        now = may;
        for (int i = mid + 1; i <= end; ++i)
            may = max(may, now += nums[i]);

        return max(answer, may);
    }

    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        return maxSub_divideConquer(nums, 0, len - 1);
    }
};

/*
    Sum - minSum Solution
    Complexity:
        Time: O(N)
        Space: O(1)
*/
class Solution {
public:
    int maxSub_maxMin(vector<int> &nums) {
        int len = nums.size();
        int sum = nums[0];
        int minSum = min(0, sum);
        int answer = nums[0];
        for (int i = 1; i < len; ++i) {
            sum += nums[i];
            answer = max(answer, sum - minSum);
            minSum = min(sum, minSum);
        }

        return answer;
    }

    int maxSubArray(vector<int>& nums) {
        return maxSub_maxMin(nums);
    }
};