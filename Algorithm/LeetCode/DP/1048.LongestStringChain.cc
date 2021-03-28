/* Meidum
Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter
anywhere in word1 to make it equal to word2.  For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1,
where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible length of a word chain with words chosen from the given list of words.

Example 1:
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chain is "a","ba","bda","bdca".

Example 2:
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5

Constraints:
1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of English lowercase letters.

Relatives:
300. Longest Increasing Subsequence
1048. Longest String Chain */

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int maxLen = 0;
        unordered_map<string, int> dp;
        dp.reserve(words.size());

        sort(words.begin(), words.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.size() < rhs.size();
        });

        for (const auto& w : words) {
            for (int i = 0; i < w.size(); ++i) {
                auto pred = w.substr(0, i) + w.substr(i+1);
                auto predLen = dp.find(pred) == dp.end() ? 1 : dp[pred] + 1;
                dp[w] = max(dp[w], predLen);
            }
            maxLen = max(dp[w], maxLen);
        }

        return maxLen;
    }
};
