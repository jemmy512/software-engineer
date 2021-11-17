/* Hard
You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi]
represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope
are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll
(i.e., put one inside the other).

Note: You cannot rotate an envelope.

Example 1:
Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

Example 2:
Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1

Constraints:
1 <= envelopes.length <= 5000
envelopes[i].length == 2
1 <= wi, hi <= 10^4

Relatives:
300. Longest Increasing Subsequence
354. Russian Doll Envelopes
1048. Longest String Chain
1996. The Number of Weak Characters in the Game */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int maxLen = 0;
        vector dp(envelopes.size(), 1);

        sort(envelopes.begin(), envelopes.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[0] != rhs[0] ? lhs[0] < rhs[0] : lhs[1] > rhs[1];
        });

        for (auto i = 0; i < envelopes.size(); ++i) {
            auto len = 0;

            for (auto j = 0; j < i; ++j) {
                if (envelopes[i][1] > envelopes[j][1]) {
                    len = max(len, dp[j]);
                }
            }

            dp[i] = len + 1;
            maxLen = max(dp[i], maxLen);
        }

        return maxLen;
    }
};