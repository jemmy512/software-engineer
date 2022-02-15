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
#include <unordered_set>
#include <unordered_map>

using namespace std;

// bottom-up solution
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

// top-down, dfs: recurstion + memorization
class Solution {
public:
    int longestStrChain(vector<string> &words) {
        unordered_set<string> wordSet{words.cbegin(), words.cend()};
        unordered_map<string, int> dp;
        dp.reserve(wrodsPresent.sisze());

        int manLen = 0;

        for (const auto& word : words) {
            manLen = max(manLen, dfs(wordSet, dp, word));
        }

        return manLen;
    }

private:
    int dfs(const unordered_set<string>& words, unordered_map<string, int>& dp, const string& word) {
        // If the word is encountered previously we just return its value present in the map (dpization).
        if (dp.find(word) != dp.end()) {
            return dp[word];
        }

        // This stores the maximum length of word sequence possible with the 'word' as the
        auto maxLength = 1;

        // creating all possible strings taking out one character at a time from the `word`
        for (auto i = 0; i < word.length(); i++) {
            auto pred = word.substr(0, i) + word.substr(i + 1);
            // If the new word formed is present in the list, we do a dfs search with this pred.
            if (words.find(pred) != words.end()) {
                auto predLen = 1 + dfs(words, dp, pred);
                maxLength = max(maxLength, predLen);
            }
        }
        dp[word] = maxLength;

        return maxLength;
    }
};