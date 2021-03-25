/* Easy
Given a non-empty string s, you may delete at most one character.
Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True

Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.

Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

Relatives:
009. Palindrome Number
125. Valid Palindrome
234. Palindrome Linked List
680. Valid Palindrome II */

#include <string>

using namespace std;

class Solution {
public:
    bool validPalindrome(string str) {
        int beg = 0;
        int end = str.size()-1;

        while (beg < end) {
            if (str[beg] != str[end]) {
                return isPalindromeRange(str, beg, end-1) || isPalindromeRange(str, beg+1, end);
            }
            ++beg;
            --end;
        }

        return true;
    }

private:
    bool isPalindromeRange(const string& str, int beg, int end) {
        while (beg < end) {
            if (str[beg++] != str[end--]) {
                return false;
            }
        }

        return true;
    }
};