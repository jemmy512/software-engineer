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
    void reverseString(vector<char>& s) {
        int b = 0, e = s.size() - 1;

        while (b < e) {
            swap(s[b++], s[e--]);
        }
    }
};