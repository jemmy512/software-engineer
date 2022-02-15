/* Medium
A string S of lowercase English letters is given.
We want to partition this string into as many parts as possible
so that each letter appears in at most one part,
and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.

Note:
S will have length in range [1, 500].
S will consist of lowercase English letters ('a' to 'z') only.

Relatives:
Relatives:
056. Merge Intervals
057. Insert Interval
252. Meeting Rooms
253. Metting Rooms II
452. Minimum Number of Arrows to Burst Balloons
435. Non-overlapping Intervals
763. Partition Labels */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> index(26);
        vector<int> result;
        result.reserve(S.size());
        int start = 0, end = 0;

        for (int i = 0; i < S.size(); ++i) {
            index[S[i]-'a'] = i;
        }

        for (int i = 0; i < S.size(); ++i) {
            end = max(end, index[S[i]-'a']);
            if (i == end) {
                result.emplace_back(end - start + 1);
                start = i + 1;
            }
        }

        return result;
    }
};