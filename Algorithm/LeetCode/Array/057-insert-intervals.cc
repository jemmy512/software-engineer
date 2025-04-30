/* Medium
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

Example 3:
Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]

Example 4:
Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]

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
1288. Remove Covered Intervals*/

#include <vector>

using namespace std;


/* Time complexity: O(N)
 * Space complexity: O(N) */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        result.reserve(intervals.size() + 1);

        int i = 0;
        int& start = newInterval[0];
        int& end = newInterval[1];

        while (i < intervals.size() && intervals[i][1] < start) {
            result.emplace_back(intervals[i]);
            ++i;
        }

        while (i < intervals.size() && intervals[i][0] <= end) {
            start = min(intervals[i][0], start);
            end = max(intervals[i][1], end);
            ++i;
        }

        result.emplace_back(newInterval);

        result.insert(result.end(), std::next(intervals.begin(), i), intervals.end());

        return result;
    }
};


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        result.reserve(intervals.size() + 1);

        int start = newInterval[0], end = newInterval[1], i = 0;
        while (i < intervals.size() && intervals[i][1] < start) {
            result.emplace_back(intervals[i]);
            ++i;
        }

        if (!result.empty() && start <= result.back()[1]) {
            result.back()[0] = min(result.back()[0], start);
            result.back()[1] = max(result.back()[1], end);
        } else {
            result.emplace_back(newInterval);
        }

        while (i < intervals.size()) {
            if (intervals[i][0] <= result.back()[1]) {
                result.back()[0] = min(result.back()[0], intervals[i][0]);
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                result.emplace_back(intervals[i]);
            }
            ++i;
        }

        return result;
    }
};

/* Time complexity: sorting O(NlogN), merge O(N) */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.emplace_back(newInterval);
        std::sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[0] < rhs[0];
        });

        vector<vector<int>> result;
        result.reserve(intervals.size());

        for (int i = 0; i < intervals.size(); ++i) {
            if (result.empty()) {
                result.emplace_back(intervals[0]);
            } else {
                if (intervals[i][0] <= result.back()[1]) {
                    result.back()[0] = min(result.back()[0], intervals[i][0]);
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                } else {
                    result.emplace_back(intervals[i]);
                }
            }
        }

        return result;
    }
};