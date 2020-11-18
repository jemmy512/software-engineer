/*
* Given a string, find the length of the longest substring without repeating characters.

Examples:
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer
must be a substring, "pwke" is a subsequence and not a substring.
*/
#include<iostream>
#include<string.h>
#include<string>
using namespace std;

int lengthOfLongestSubstring(string str) {
    constexpr int MAX_CHAR = 256;
    std::array<int, MAX_CHAR> charSet;
    charSet.fill(-1);

    int maxLen = 0;
    int lastPos = -1;
    for (int i = 0; i < str.size(); ++i) {
        if (lastPos < charSet[str[i]])
            lastPos = charSet[str[i]];
        charSet[str[i]] = i;
        maxLen = maxLen > i - lastPos ? maxLen : i - lastPos;
    }

    return maxLen;
}

int main() {
    cout << "result: " << lengthOfLongestSubstring("abcabcbb") << endl;

    cout << "result: " << lengthOfLongestSubstring("a") << endl;

    cout << "result: " << lengthOfLongestSubstring(" ") << endl;

    cout << "result: " << lengthOfLongestSubstring("") << endl;
}