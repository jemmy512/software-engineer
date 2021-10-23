/* Medium
Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

You can assume that you can always reach the last index.

Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. 
Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2

Constraints:
1 <= nums.length <= 104
0 <= nums[i] <= 1000 */

#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int jumps = 0;
        int jumpEnd = 0;
        int farthest = 0;
        
        for (auto i = 0; i < nums.size()-1; ++i) {
            farthest = max(farthest, i + nums[i]);
            
            if (i == jumpEnd) {
                ++jumps;
                jumpEnd = farthest;
            }
        }
        
        return jumps;
    }
};


/* DP time out */
class Solution {
public:
    int jump(vector<int>& nums) {
        _Memo = vector(nums.size(), INT_MAX);
        return dp(nums, 0);
    }

private:
    int dp(const vector<int>& nums, int pos) {
        if (pos >= nums.size() - 1)
            return 0;

        if (_Memo[pos] != INT_MAX)
            return _Memo[pos];

        for (auto i = 0; i < nums[pos]; ++i) {
            auto steps = dp(nums, pos + i);
            _Memo[pos] = max(_Memo[pos], steps + 1);
        }

        return _Memo[pos];
    }

private:
    vector<int> _Memo;
};