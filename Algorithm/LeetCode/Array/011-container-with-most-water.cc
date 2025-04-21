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
        int maxArea = 0, beg = 0, end = height.size() - 1;

        while (beg < end) {
            int curArea = std::min(height[beg], height[end]) * (end - beg);
            maxArea = std::max(maxArea, curArea);
            if (height[beg] < height[end]) {
                beg++;
            } else {
                end--;
            }
        }
        return maxArea;
    }
};

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int area;
        int beg = 0;
        int end = height.size() - 1;
        while (beg < end) {
            // The area is determined by the shorter edge
            // area = (end - beg) * min(height[beg], height[end]);
            area = (end - beg) * (height[beg] < height[end] ? height[beg] : height[end]);
            // maxArea = max(area, maxArea);
            maxArea = area > maxArea ? area : maxArea;
            // because the area is decided by the shorter edge
            // so we increase the area is to increase the shorter edge
            //
            //     height[beg] < height[end] ? beg++ : end-- ;
            //
            // However, the above code could cause the unnecessary `area` cacluation
            // We can do some improvement as below:
            if (height[beg] < height[end]) {
                int cur = beg;
                do {
                    ++beg;
                } while (beg < end && height[cur] >= height[beg]);
            } else {
                int cur = end;
                do {
                    --end;
                } while (beg < end && height[cur] >= height[end]);
            }
        }

        return maxArea;
    }
};