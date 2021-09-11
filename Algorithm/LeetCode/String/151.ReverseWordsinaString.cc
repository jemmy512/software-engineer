/* Medium
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
For C programmers, try to solve it in-place in O(1) extra space. */

#include <cstdio>
#include <memory>
#include <iostream>
#include <sstream>

using std::string;

// iterate from end -> begin
class Solution {
public:
    string reverseWords(string s) {
        string result;
        result.reserve(s.size());
        int beg = s.size()-1;
        int end = s.size()-1;
        bool isFirstWord = true;

        while (end >=0) {
            end = beg;
            while (end >=0 && s[end] == ' ') { --end; };
            
            beg = end;
            while (beg >=0 && s[beg] != ' ') { --beg; };

            if (end >= 0) {
                if (isFirstWord) {
                    isFirstWord = false;
                } else {
                    result += " ";
                }
                result += s.substr(beg+1, end-beg);
            }

            end = beg;
        }

        return result;
    }
};

// iterate from begin -> end
class Solution {
public:
    string reverseWords(string s) {
        vector<string> vec;
        size_t beg = 0;
        size_t end = 0;
        
        while (end < s.size()) {
            beg = end;
            while (beg < s.size() && s[beg] == ' ')
                ++beg;
            
            end = beg;
            while (end < s.size() && s[end] != ' ')
                ++end;
            
            if (beg < s.size())
                vec.emplace_back(s.substr(beg, end-beg));
        }
        
        string result;
        result.reserve(s.size());
        
        for (int i = vec.size()-1; i >= 0; --i) {
            result.append(vec[i]);
            if (i != 0)
                result.append(" ");
        }
        
        return result;
    }
};