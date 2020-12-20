/* Medium
Given a string, find the length of the longest substring without repeating characters.

Examples:
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer
must be a substring, "pwke" is a subsequence and not a substring.

Reletives:
3. Longest Substring Without Repeating Characters
159. Longest Substring with At Most Two Distinct Characters
340. Longest Substring with At Most K Distinct Characters
239. Sliding Window Maximum
992. Subarrays with K Different Integers */

#include <iostream>
#include <cstring>
#include <string>
#include <array>

using namespace std;

/* Sliding windown*/
int lengthOfLongestSubstring(string str) {
    constexpr int MAX_CHAR = 256;
    std::array<int, MAX_CHAR> charSet;
    charSet.fill(-1);
    int maxLen = 0;

    for (int start = -1, end = 0; end < str.size(); ++end) {
        if (charSet[str[end]] != -1) {
            start = max(start, charSet[str[end]]); // abcbade
        }
        charSet[str[end]] = end;
        maxLen = max(maxLen, end - start);
    }

    return maxLen;
}

int main() {
    cout << "result: " << lengthOfLongestSubstring("abcabcbb") << endl;

    cout << "result: " << lengthOfLongestSubstring("a") << endl;

    cout << "result: " << lengthOfLongestSubstring(" ") << endl;

    cout << "result: " << lengthOfLongestSubstring("") << endl;
}