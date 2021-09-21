/* Medium
Given an array of meeting time intervals consisting of start and end times
[[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

Example 1:
Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:
Input: [[7,10],[2,4]]
Output: 1

Relatives:
056. Merge Intervals
057. Insert Interval
252. Meeting Rooms
253. Metting Rooms II
452. Minimum Number of Arrows to Burst Balloons
435. Non-overlapping Intervals
763. Partition Labels
1094. Car Pooling */

#include <vector>
#include <queue>

using namespace std;

/* Priority Queue
 * Time complexity: O(NlogN) */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;

        std::sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[0] < rhs[0];
        });

        std::priority_queue<int, vector<int>, std::greater<int>> minHeap;

        for (const auto& inter : intervals) {
            if (!minHeap.empty() && inter[0] >= minHeap.top()) {
                minHeap.pop();
            }
            minHeap.emplace(inter[1]);
        }

        return minHeap.size();
    }
};

/* Chronological Ordering
 * Time complexity: O(NlogN) */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;

        vector<int> startTimes;
        startTimes.reserve(intervals.size());
        vector<int> endTimes;
        endTimes.reserve(intervals.size());

        for (const auto& inter : intervals) {
            startTimes.emplace_back(inter[0]);
            endTimes.emplace_back(inter[1]);
        }

        std::sort(startTimes.begin(), startTimes.end(), std::less<int>());
        std::sort(endTimes.begin(), endTimes.end(), std::less<int>());

        int start = 0, end = 0;
        int rooms = 0;
        while (start < startTimes.size()) {
            if (startTimes[start] >= endTimes[end]) {
                ++end;
            } else {
                ++rooms;
            }
            ++start;
        }

        return rooms;
    }
};


/* Iterator all rooms:
 * Time complexity: O(N^2) */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;

        std::sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[0] < rhs[0];
        });

        vector<pair<int, int>> rooms;
        rooms.reserve(intervals.size());
        rooms.emplace_back(intervals[0][0], intervals[0][1]);

        for (int i = 1; i < intervals.size(); ++i) {
            bool added = false;
            for (auto& [start, end] : rooms) {
                if (intervals[i][0] >= end) {
                    end = intervals[i][1];
                    added = true;
                    break;
                }
            }

            if (!added) {
                rooms.emplace_back(intervals[i][0], intervals[i][1]);
            }
        }

        return rooms.size();
    }
};