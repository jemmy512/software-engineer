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
    const int MAX_CHAR = 256;
    int arr[MAX_CHAR];
    memset(arr, -1, sizeof(arr));
    int maxLen = 0;
    int lastRepeatPos = -1;
    for (int i = 0; i < str.size(); ++i) {
        if (lastRepeatPos < arr[str[i]])
            lastRepeatPos = arr[str[i]];
        arr[str[i]] = i;
        maxLen = maxLen > i - lastRepeatPos ? maxLen : i - lastRepeatPos;
    }
    return maxLen;
}

int main() {
    string s1= "abcabcbb";
    cout << "result: " << lengthOfLongestSubstring(s1) << endl;
}