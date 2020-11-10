/*
Difficulty: Easy

Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".
*/

// 467 test cases, 10ms, beat 97.83%
#include <string>
using std::string;

class Solution {
public:
    string reverseString(string s) {
        int len = s.size()-1;
        for (int i = 0; i < len-i; ++i) {
            std::swap(s[i], s[len-i]);
        }
        return s;
    }
};