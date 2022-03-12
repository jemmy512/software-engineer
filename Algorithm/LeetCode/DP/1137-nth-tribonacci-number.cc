/* Easy
The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

Example 1:
Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:
Input: n = 25
Output: 1389537

Constraints:
0 <= n <= 37
The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1. */

class Solution {
public:
    int tribonacci(int N) {
        if (N == 0)
            return 0;
        else if (N == 1 || N == 2)
            return 1;

        int prevOne = 1;
        int prevTwo = 1;
        int prevThree = 0;

        for (int i = 3; i <= N; ++i) {
            int cur = prevOne + prevTwo + prevThree;
            prevThree = prevTwo;
            prevTwo = prevOne;
            prevOne = cur;
        }

        return prevOne;
    }
};