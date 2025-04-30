/* Medium
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


Constraints:
1 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4

Relatives:
56. Merge Intervals
57. Insert Interval
252. Meeting Rooms
253. Meeting Rooms II
495. Teemo Attacking
616. Add Bold Tag in String
715. Range Module - Hard
759. Employee Free Time - Hard
763. Partition Labels
986. Interval List Intersections */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return (lhs[0] < rhs[0]);
        });

        vector<vector<int>> ret;
        ret.emplace_back(intervals[0]);

        for (auto i = 0; i < intervals.size(); ++i) {
            if (intervals[i][0] <= ret.back()[1]) {
                ret.back()[1] = max(ret.back()[1], intervals[i][1]);
            } else {
                ret.emplace_back(intervals[i]);
            }
        }

        return ret;
    }
};