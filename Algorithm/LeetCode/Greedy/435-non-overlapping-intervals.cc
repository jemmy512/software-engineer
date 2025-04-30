/* Medium
Given an array of intervals intervals where intervals[i] = [starti, endi],
return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.


Constraints:
1 <= intervals.length <= 10^5
intervals[i].length == 2
-5 * 104 <= starti < endi <= 5 * 10^4

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
#include <algorithm>

using namespace std;

/* minimum remove means if two intervals have same start time, remove the long one.
If sort by start time, the first inteval will be the longer one
when first two intervals have same start time,
the long one will be reserved, this doesn't meet the requirment.

Sort by end time will sort the long one after the short one.

E.g., [[1,100],[11,22],[1,11],[2,12]]
Sort by start time;
1                       100
1       11
    2       12
        11      22

Sort by end time:
1       11
    2       12
        11      22
1                       100 */

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[1] < rhs[1];
        });

        auto end = 0;
        auto result = 0;

        for (auto  i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < intervals[end][1]) {
                ++result;
            } else {
                end = i;
            }
        }

        return result;
    }
};