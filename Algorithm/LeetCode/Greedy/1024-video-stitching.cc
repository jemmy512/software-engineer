/* Medium
You are given a series of video clips from a sporting event that lasted time seconds.
These video clips can be overlapping with each other and have varying lengths.

Each video clip is described by an array clips where clips[i] = [starti, endi] indicates
that the ith clip started at starti and ended at endi.

We can cut these clips into segments freely.

For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
Return the minimum number of clips needed so that we can cut the clips into segments
that cover the entire sporting event [0, time]. If the task is impossible, return -1.


Example 1:
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
Output: 3
Explanation:
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

Example 2:
Input: clips = [[0,1],[1,2]], time = 5
Output: -1
Explanation: We can't cover [0,5] with only [0,1] and [1,2].

Example 3:
Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]],
time = 9
Output: 3
Explanation: We can take clips [0,4], [4,7], and [6,9].

Example 4:
Input: clips = [[0,4],[2,8]], time = 5
Output: 2
Explanation: Notice you can have extra video after the event ends.

Constraints:
1 <= clips.length <= 100
0 <= starti <= endi <= 100
1 <= time <= 100

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

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        sort(clips.begin(), clips.end(), [](const auto& lhs, const auto& rhs) {
            return (lhs[0] != rhs[0]) ? (lhs[0]  < rhs[0]) : (lhs[1] > rhs[1]);
        });

        int i = 0;
        int cnt = 0;
        int curEnd = 0;

        while (i < clips.size() && clips[i][0] <= curEnd) {
            int nextEnd = curEnd;
            while (i < clips.size() && clips[i][0] <= curEnd) {
                nextEnd = max(nextEnd, clips[i][1]);
                ++i;
            }

            ++cnt;
            curEnd = nextEnd;

            if (curEnd >= time) {
                return cnt;
            }
        }

        return -1;
    }
};