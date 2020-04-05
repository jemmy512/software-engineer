/*
Difficulty: Easy

Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".
*/

// 467 test cases, 10ms, beat 97.83%
class Solution {
public:
    string reverseString(string s) {
        int len = s.size();
        for (int i = 0, j = len - 1; i < j; ++i, --j) {
            swap(s[i], s[j]);
        }
        return s;
    }
};