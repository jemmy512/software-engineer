/* Hard
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9

Constraints:
n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5

Relativeness:
011. Container With Most Water
042. Trapping Rain Water
407. Trapping Rain Water II
238. Product of Array Except Self
755. Pour Water */

#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        const auto size = height.size();
        int ret = 0;
        int left = 0, right = size - 1;
        int maxL = 0, maxR = 0;

        while (left < right) {
            maxL = max(maxL, height[left]);
            maxR = max(maxR, height[right]);
            ret += (maxL < maxR) ? (maxL - height[left++]) : (maxR - height[right--]);
        }

        return ret;
    }
};

class Solution {
public:
    int trap(vector<int>& height) {
        const auto size = height.size();
        vector<int> maxL(size);
        vector<int> maxR(size);

        maxL[0] = height[0];
        maxR[size-1] = height[size-1];

        for (auto i = 1; i < size; ++i) {
            maxL[i] = max(height[i], maxL[i-1]);
        }

        for (int i = size - 2; i >= 0; --i) {
            maxR[i] = max(height[i], maxR[i+1]);
        }

        int ret = 0;

        for (auto i = 1; i < size - 1; ++i) {
            ret += min(maxL[i], maxR[i]) - height[i];
        }

        return ret;
    }
};