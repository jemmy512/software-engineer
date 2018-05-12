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

/*
    Dynamic Solution
    Complexity:
        Time: O(N)
        Space: O(1)
*/
class Solution {
public:
    int maxSub_dp(vector<int> &nums) {
        int len = nums.size();
        int prev = nums[0];
        int answer = nums[0];
        int beg = 0, end = 0;
        for (int i = 1; i < len; ++i) {
            if (prev + nums[i] < nums[i])
                beg = i;
            prev = max(prev + nums[i], nums[i]);
            if (prev > answer)
                end = i;
            answer = max(prev, answer);
        }
        cout << beg << ", " << end << endl;
        return answer;
    }
    
    int maxSubArray(vector<int>& nums) {
        return maxSub_dp(nums);
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