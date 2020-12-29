/* Medium
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest.
If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters. */

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> hashMap;
        hashMap.reserve(words.size());

        for (const auto& word : words) {
            ++hashMap[word];
        }

        auto comparator = [](const auto& lhs, const auto& rhs) {
            return lhs.second > rhs.second || (lhs.second == rhs.second && lhs.first < rhs.first);
        };

        using T = pair<string, int>;
        priority_queue<T, vector<T>, decltype(comparator)> que(comparator);
        for (const auto& pa : hashMap) {
            que.push(pa);
        }

        vector<string> result;
        result.reserve(k);

        while (k--) {
            result.emplace_back(que.top().first);
            que.pop();
        }

        return result;
    }
};