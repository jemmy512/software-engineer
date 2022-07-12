/* Hard
Given an array of integers heights representing the histogram's bar height
where the width of each bar is 1,
return the area of the largest rectangle in the histogram.

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4

Constraints:
1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4

Relatives:
084. Largest Rectangle in Histogram
085. Maximal Rectangle
221. Maximal Square */

#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        const auto size = heights.size();
        stack<int> stk;
        int ret = 0;
        int i = 0;

        while (i < size) {
            if (stk.empty() || heights[i] >= heights[stk.top()]) {
                stk.push(i++);
            } else {
                auto h = heights[stk.top()]; stk.pop();
                auto w = stk.empty() ? i : i - stk.top() - 1;
                ret = max(ret, h * w);
            }
        }

        return ret;
    }
};

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        stk.push(-1);
        int maxArea = 0;

        for (size_t i = 0; i < heights.size(); i++) {
            while (stk.top() != -1 and heights[stk.top()] >= heights[i]) {
                int height = heights[stk.top()];
                stk.pop();
                int width = i - stk.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            stk.push(i);
        }

        while (stk.top() != -1) {
            int height = heights[stk.top()];
            stk.pop();
            int width = heights.size() - stk.top() - 1;
            maxArea = max(maxArea, height * width);
        }

        return maxArea;
    }
};