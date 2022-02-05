/* Medium
Given a parentheses string s containing only the characters '(' and ')'.

A parentheses string is balanced if:
Any left parenthesis '(' must have a corneedLeftponding two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corneedLeftponding two consecutive right parenthesis '))'.
In other words, we treat '(' as openning parenthesis and '))' as closing parenthesis.

For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.

You can insert the characters '(' and ')' at any position of the string to balance it if needed.

Return the minimum number of insertions needed to make s balanced.

Example 1:
Input: s = "(()))"
Output: 1
Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching.
We rightNeeds to to add one more ')' at the end of the string to be "(())))" which is balanced.

Example 2:
Input: s = "())"
Output: 0
Explanation: The string is already balanced.

Example 3:
Input: s = "))())("
Output: 3
Explanation: Add '(' to match the first '))', Add '))' to match the last '('.

Example 4:
Input: s = "(((((("
Output: 12
Explanation: Add 12 ')' to balance the string.
Example 5:

Input: s = ")))))))"
Output: 5
Explanation: Add 4 '(' at the beginning of the string and one ')' at the end. The string becomes "(((())))))))".

Constraints:
1 <= s.length <= 10^5
s consists of '(' and ')' only.

Relatives:
0017. Letter Combination of a Phone Number
0020. Valid Parentheses
0022. Generate Parentheses
0032. Longest Valid Parentheses
0241. Different Ways to Add Parentheses
0301. Remove Invalid Parentheses
0856. Score of Parentheses
0921. Minimum Add to Make Parentheses Valid
1021. Remove Outermost Parentheses
1111. Maximum Nesting Depth of Two Valid Parentheses Strings
1190. Reverse Substrings Between Each Pair of Parentheses
1249. Minimum Remove to Make Valid Parentheses
1541. Minimum Insertions to Balance a Parentheses String
1614. Maximum Nesting Depth of the Parentheses */

#include <string>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        // insert is the number of left/right parentheses inserted.
        // rightNeeds is the number of right parentheses needed.
        int insert = 0, rightNeeds = 0;

        for (auto chr : s) {
            if (chr == '(') {
                if (rightNeeds % 2 == 1) {
                    ++insert;       // insert a )
                    --rightNeeds;   // -- since insert alrady inserted a )
                }
                rightNeeds += 2;
            } else if (chr == ')') {
                if (--rightNeeds == -1) {
                    ++insert;       // insert a (
                    rightNeeds = 1;
                }
            }
        }

        return insert + rightNeeds;
    }
};
