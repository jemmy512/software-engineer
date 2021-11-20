/* Medium
There are n bulbs that are initially off. You first turn on all the bulbs,
then you turn off every second bulb.

On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on).
For the ith round, you toggle every i bulb. For the nth round, you only toggle the last bulb.

Return the number of bulbs that are on after n rounds.

Example 1:
Input: n = 3
Output: 1
Explanation: At first, the three bulbs are [off, off, off].
After the first round, the three bulbs are [on, on, on].
After the second round, the three bulbs are [on, off, on].
After the third round, the three bulbs are [on, off, off].
So you should return 1 because there is only one bulb is on.

Example 2:
Input: n = 0
Output: 0

Example 3:
Input: n = 1
Output: 1

Constraints:
0 <= n <= 10^9

IF a bulb is on that means it is switched odd times:
6 = 1 * 6 = 2 * 3 // 4 times, on
16 = 1 * 16  = 2 * 8 = 4 * 4 // 5 times, off */

#include <cmath>

class Solution {
public:
    int bulbSwitch(int n) {
        return (int)sqrt(n);
    }
};