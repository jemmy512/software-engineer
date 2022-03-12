/* Hard
Given two words word1 and word2,
find the minimum number of operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:
Insert a character
Delete a character
Replace a character

Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

Constraints:
0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.

Refer: https://www.youtube.com/watch?v=q6OWnp9cteA
Well, you may have noticed that each time when we update dp[i][j],
we only need dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j].
In fact, we need not maintain the full m*n matrix.
Instead, maintaing one column is enough.
The code can be optimized to O(m) or O(n) space,
depending on whether you maintain a row or a column of the original matrix.

Relatives:
161. One Edit Distance
583. Delete Operation for Two Strings
712. Minimum ASCII Delete Sum for Two Strings
1035. Uncrossed Lines

392. Is Subsequence */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string src, string dst) {
        if (src.empty() || dst.empty())
            return src.size() + dst.size();

        vector dp(dst.size()+1, 0);

        for (int i = 0; i <= src.size(); ++i) {
            int last;
            for (int j = 0; j <= dst.size(); ++j) {
                if (i == 0) {
                    dp[j] = j;
                } else if (j == 0) {
                    last = dp[j];
                    dp[j] = i;
                } else {
                    int temp = dp[j];
                    dp[j] = min((src[i-1] == dst[j-1] ? 0 : 1) + last, min(dp[j-1], dp[j]) + 1);
                    last = temp;
                }
            }
        }

        return dp[dst.size()];
    }
};

/* This is a classic problem of Dynamic Programming.
We define the state dp[i][j] to be the minimum number of operations to convert word1[0..i - 1] to word2[0..j - 1].
The state equations have two cases: the boundary case and the general case.
Note that in the above notations, both i and j take values starting from 1.

For the boundary case, that is, to convert a string to an empty string,
it is easy to see that the mininum number of operations
to convert word1[0..i - 1] to "" requires at least i operations (deletions).

In fact, the boundary case is simply:
dp[i][0] = i;
dp[0][j] = j.

Now let's move on to the general case, that is,
convert a non-empty word1[0..i - 1] to another non-empty word2[0..j - 1].
Well, let's try to break this problem down into smaller problems (sub-problems).

Suppose we have already known how to convert word1[0..i - 2] to word2[0..j - 2], which is dp[i - 1][j - 1].
Now let's consider word[i - 1] and word2[j - 1].
If they are euqal, then no more operation is needed and dp[i][j] = dp[i - 1][j - 1].

Well, what if they are not equal?
If they are not equal, we need to consider three cases:
1. Replace word1[i - 1] by word2[j - 1] (dp[i][j] = dp[i - 1][j - 1] + 1 (for replacement));
2. Delete word1[i - 1] and word1[0..i - 2] = word2[0..j - 1] (dp[i][j] = dp[i - 1][j] + 1 (for deletion));
3. Insert word2[j - 1] to word1[0..i - 1] and word1[0..i - 1] + word2[j - 1] = word2[0..j - 1]
    (dp[i][j] = dp[i][j - 1] + 1 (for insertion)).

Make sure you understand the subtle differences between the equations for deletion and insertion.
For deletion, we are actually converting word1[0..i - 2] to word2[0..j - 1],
which costs dp[i - 1][j], and then deleting the word1[i - 1],
which costs 1. The case is similar for insertion. */

// bottom up
class Solution {
public:
    int minDistance(string src, string dst) {
        int lenSrc = src.length();
        int lenDst = dst.length();
        if (!lenSrc || !lenDst)
            return lenSrc + lenDst;

        vector dp(lenSrc+1, vector(lenDst+1, 0));

        for (int i = 0; i <= lenSrc; ++i) {
            for (int j = 0; j <= lenDst; ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = i + j;
                } else {
                    if (src[i-1] == dst[j-1]) {
                        dp[i][j] = dp[i-1][j-1];
                    } else {
                        dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    }
                }
            }
        }

        return dp[lenSrc][lenDst];
    }
};

// top down
class Solution {
public:
    int minDistance(string src, string dst) {
        Memo.resize(src.size(), vector(dst.size(), -1));

        return dp(src, src.size()-1, dst, dst.size()-1);
    }

private:
    // return min edit distance between src[0..i] and dst[0..j]
    int dp(const string& src, int i, const string& dst, int j) {
        if (i == -1)
            return j + 1;
        if (j == -1)
            return i + 1;

        if (Memo[i][j] != -1)
            return Memo[i][j];

        if (src[i] == dst[j]) {
            Memo[i][j] = dp(src, i - 1, dst, j - 1);
        } else {
            Memo[i][j] =  1 + min({
                dp(src, i, dst, j - 1),     // insert
                dp(src, i - 1, dst, j),     // delete
                dp(src, i - 1, dst, j - 1)  // replace
            });
        }

        return Memo[i][j];
    }

private:
    // min edit distance between src[0..i] and dst[0..j]
    vector<vector<int>> Memo;
};