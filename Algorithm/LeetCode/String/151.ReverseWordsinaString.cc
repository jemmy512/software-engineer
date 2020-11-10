/*
Given an input string, reverse the string word by word.



Example 1:

Input: "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: "  hello world!  "
Output: "world! hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.


Note:

A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces. However, your reversed string should not contain
leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.


Follow up:

For C programmers, try to solve it in-place in O(1) extra space.
*/
#include <cstdio>
#include <memory>
#include <iostream>
#include <sstream>

using std::string;

class Solution {
public:
    string reverseWords(string s) {
        std::stringstream ss;

        int beg = s.size()-1;
        int end = s.size()-1;
        bool isFirstWord = true;

        while (beg >=0 && end >=0) {
            while (end >=0 && s[end] == ' ') { --end; };
            beg = end;
            while (beg >=0 && s[beg] != ' ') { --beg; };

            if (beg != end) {
                if (isFirstWord) {
                    isFirstWord = false;
                } else {
                    ss << " ";
                }
                ss << s.substr(beg+1, end-beg);
            }

            end = beg;
        }

        return ss.str();
    }
};


int main() {
    Solution slu;
    std::cout << "[" << slu.reverseWords("") << "]" << std::endl;
}