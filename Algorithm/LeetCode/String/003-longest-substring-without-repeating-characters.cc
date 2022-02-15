/* Medium
Given a string, find the length of the longest substring without repeating characters.

Examples:
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer
must be a substring, "pwke" is a subsequence and not a substring.

Reletives:
003. Longest Substring Without Repeating Characters
159. Longest Substring with At Most Two Distinct Characters
340. Longest Substring with At Most K Distinct Characters
239. Sliding Window Maximum
992. Subarrays with K Different Integers */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/* Sliding windown */
int lengthOfLongestSubstring(string str) {
    vector<int> index(256, -1);
    int maxLen = 0;

    for (auto beg = -1, end = 0; end < str.size(); ++end) {
        if (index[str[end]] != -1) {
            beg = max(beg, index[str[end]]); // abcbade
        }
        index[str[end]] = end;
        maxLen = max(maxLen, end - beg);
    }

    // for (auto beg = 0, end = 0; end < str.size(); ++end) {
    //     if (index[str[end]] != -1) {
    //         beg = beg > index[str[end]] ? beg : index[str[end]] + 1;
    //     }
    //     index[str[end]] = end;
    //     maxLen = max(maxLen, end - beg);
    // }

    return maxLen;
}

/* Sliding windown */
int lengthOfLongestSubstring(string s) {
    int maxLen = 0;
    int beg = 0, end = 0;
    unordered_map<char, int> dict;

    while (end < s.size()) {
        auto chrEnd =  s[end++];
        ++dict[chrEnd];

        while (dict[chrEnd] > 1) {
            auto chrBeg = s[beg++];
            --dict[chrBeg];
        }

        maxLen = max(maxLen, end - beg);
    }

    return maxLen;
}

int main() {
    cout << "result: " << lengthOfLongestSubstring("abcabcbb") << endl;

    cout << "result: " << lengthOfLongestSubstring("a") << endl;

    cout << "result: " << lengthOfLongestSubstring(" ") << endl;

    cout << "result: " << lengthOfLongestSubstring("") << endl;
}