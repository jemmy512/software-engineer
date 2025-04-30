/* Medium
here are some spherical balloons spread in two-dimensional space.
For each balloon, provided input is the start and end coordinates of the horizontal diameter.
Since it's horizontal, y-coordinates don't matter, and hence the x-coordinates of start
and end of the diameter suffice. The start is always smaller than the end.

An arrow can be shot up exactly vertically from different points along the x-axis.
A balloon with start and end bursts by an arrow shot at x if start ≤ x ≤ end.
There is no limit to the number of arrows that can be shot. An arrow once shot keeps traveling up infinitely.

Given an array points where points[i] = [start, end], return the minimum number
of arrows that must be shot to burst all balloons.


Example 1:
Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: One way is to shoot one arrow for example at x = 6
(bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).

Example 2:
Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4

Example 3:
Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2

Example 4:
Input: points = [[1,2]]
Output: 1

Example 5:
Input: points = [[2,3],[2,3]]
Output: 1

Constraints:
0 <= points.length <= 10^4
points[i].length == 2
-2^31 <= start < end <= 2^31 - 1

Relatives:
056. Merge Intervals
057. Insert Interval
252. Meeting Rooms
253. Metting Rooms II
452. Minimum Number of Arrows to Burst Balloons
435. Non-overlapping Intervals
763. Partition Labels
986. Interval List Intersections
1024. Video Stitching
1288. Remove Covered Intervals */

#include <vector>

using namespace std;

/* Greedy algorithms: sort by end coordinate */
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
       if (points.empty())
            return 0;

        std::sort(points.begin(), points.end(), [](const auto& lhs, const auto& rhs) {
           return lhs[1] < rhs[1];
        });

        int arrows = 1;
        int prevEnd = points[0][1];

        for (const auto& point : points) {
            if (point[0] > prevEnd) {
                ++arrows;
                prevEnd = point[1];
            }
        }

        return arrows;
    }
};

/* Greedy algorithms: sort by end coordinate */
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
       if (points.empty())
            return 0;

        std::sort(points.begin(), points.end(), [](const auto& lhs, const auto& rhs) {
           return lhs[1] < rhs[1];
        });

        int arrows = 1;
        int prevEnd = points[0][1];

        for (const auto& point : points) {
            // if the current balloon starts after the end of another one,
            // one needs one more arrow
            if (prevEnd < point[0]) {
                ++arrows;
                prevEnd = point[1];
            }
        }

        return arrows;
    }
};

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
       if (points.empty())
            return 0;

        std::sort(points.begin(), points.end(), [](const auto& lhs, const auto& rhs) {
           return lhs[0] < rhs[0];
        });

        vector<pair<int, int>> arrows;
        arrows.reserve(points.size());
        arrows.emplace_back(points[0][0], points[0][1]);

        for (int i = 1; i < points.size(); ++i) {
            auto& [start, end] = arrows.back();
            if (points[i][0] <= end) {
                start = max(start, points[i][0]);
                end = min(end, points[i][1]);
            } else {
                arrows.emplace_back(points[i][0], points[i][1]);
            }
        }

        return arrows.size();
    }
};