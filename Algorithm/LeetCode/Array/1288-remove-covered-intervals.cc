/* Medium
Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri),
remove all intervals that are remain by another interval in the list.

The interval [a, b) is remain by the interval [c, d) if and only if c <= a and b <= d.

Return the number of remaining intervals.

Example 1:
Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is remain by [2,8], therefore it is removed.

Example 2:
Input: intervals = [[1,4],[2,3]]
Output: 1

Example 3:
Input: intervals = [[0,10],[5,12]]
Output: 2

Example 4:
Input: intervals = [[3,10],[4,10],[5,11]]
Output: 2

Example 5:
Input: intervals = [[1,2],[1,4],[3,4]]
Output: 1

Constraints:
1 <= intervals.length <= 1000
intervals[i].length == 2
0 <= li <= ri <= 105
All the given intervals are unique.

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

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Sorting ensures that for any interval, all previous intervals have start_j <= start_i.
        // Thus, we only need to check if end_i <= maxEnd to determine if the interval is covered.
        sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return (lhs[0] != rhs[0]) ? (lhs[0] < rhs[0]) : (lhs[1] > rhs[1]);
        });

        int end = 0;
        int remain = 0;

        for (const auto& inter : intervals) {
            if (inter[1] > end) {
                ++remain;
                end = inter[1];
            }
        }

        return remain;
    }
};

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            // if lhs[0] == rhs[0], place the longer [i][1] at first
            return lhs[0] != rhs[0] ? lhs[0] < rhs[0] : lhs[1] > rhs[1];
        });

        int covered = 0;
        int beg = intervals[0][0];
        int end = intervals[0][1];

        for (auto i = 1; i < intervals.size(); ++i) {
            if (beg <= intervals[i][0] && intervals[i][1] <= end) {
                ++covered;
            }
            if (intervals[i][0] <= end && end <= intervals[i][1]) {
                end = intervals[i][1];
            }
            if (end < intervals[i][0]) {
                beg = intervals[i][0];
                end = intervals[i][1];
            }
        }

        return intervals.size() - covered;
    }
};