/* Easy
We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to the rightmost position. 
For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. 
Return True if and only if A can become B after some number of shifts on A.

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false

Note:
A and B will have length at most 100.

Constraints:
1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool rotateString(string A, string B) {
        return (A.size() == B.size()) && ((A + A).find(B) != string::npos);
    }
};