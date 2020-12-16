/* Medium
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]

Constraints:
1 <= n <= 8

Relatives:
017. Letter Combination of a Phone Number
020. validParentheses
022. Generate Parentheses */

#include <vector>
#include <string>

using namespace std;

/* Approach: backtrack */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        max = n;
        backtrack("", 0, 0);
        return vec;
    }

private:
    void backtrack(string cur, int open, int close) {
        if (cur.size() == 2 * max) {
            vec.push_back(cur);
            return;
        }

        if (open < max)
            backtrack(cur+"(", open+1, close);
        if (close < open)
            backtrack(cur+")", open, close+1);
    }

private:
    int max;
    vector<string> vec;
};