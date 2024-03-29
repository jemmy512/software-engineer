/* Medium
Given n non-negative integers a1, a2, ..., an,
where each represents a point at coordinate (i, ai).
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
Find two lines, which together with x-axis forms a container,
such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

Relativeness:
011. Container With Most Water
042. Trapping Rain Water
407. Trapping Rain Water II
238. Product of Array Except Self
755. Pour Water */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0, left = 0, right = height.size() - 1;

        while (left < right) {
            int curArea = std::min(height[left], height[right]) * (right - left);
            maxArea = std::max(maxArea, curArea);
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
};

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int area;
        int left = 0;
        int right = height.size() - 1;
        while (left < right) {
            // The area is determined by the shorter edge
            // area = (right - left) * min(height[left], height[right]);
            area = (right - left) * (height[left] < height[right] ? height[left] : height[right]);
            // maxArea = max(area, maxArea);
            maxArea = area > maxArea ? area : maxArea;
            // because the area is decided by the shorter edge
            // so we increase the area is to increase the shorter edge
            //
            //     height[left] < height[right] ? left++ : right-- ;
            //
            // However, the above code could cause the unnecessary `area` cacluation
            // We can do some improvement as below:
            if (height[left] < height[right]) {
                int cur = left;
                do {
                    ++left;
                } while (left < right && height[cur] >= height[left]);
            } else {
                int cur = right;
                do {
                    --right;
                } while (left < right && height[cur] >= height[right]);
            }
        }

        return maxArea;
    }
};