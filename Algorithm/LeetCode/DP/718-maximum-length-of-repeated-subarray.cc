/* Medium
Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:
Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation:
The repeated subarray with maximum length is [3, 2, 1].

Note:
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100

Relatives:
209. Minimum Size Subarray Sum
718. Maximum Length of Repeated Subarray */

#include <algorithm>
#include <vector>

using namespace std;

/* bottom up
 * dp[i][j] = dp[i+1][j+1] + 1 */
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int maxLen = 0;
        vector dp(A.size()+1, vector(B.size()+1, 0));

        for (int i = A.size()-1; i >=0; --i) {
            for (int j = B.size()-1; j >=0; --j) {
                if (A[i] == B[j]) {
                    dp[i][j] = dp[i+1][j+1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                }
            }
        }

        return maxLen;
    }
};

/* bottom up
 * dp[i][j] = dp[i-1][j-1] + 1 */
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int maxLen = 0;
        vector dp(A.size()+1, vector(B.size()+1, 0));

        for (auto i = 1; i <= A.size(); ++i) {
            for (auto j = 1; j <= B.size(); ++j) {
                if (A[i-1] == B[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                }
            }
        }

        return maxLen;
    }
};
