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
0 <= n <= 10^9 */

#include <cmath>

/* A bulb ends up on if it is switched an odd number of times.

Call them bulb 1 to bulb n. Bulb i is switched in round d if and only if d divides i.
So bulb i ends up on if and only if it has an odd number of divisors.

Divisors come in pairs, like i = 6 = 1 * 6 = 2 * 3.
Except when i is a square, like 16 = 1 * 16  = 2 * 8 = 4 * 4, and double divisor 4.
So bulb i ends up on if and only if i is a square.

So just count the square numbers.

Let R = int(sqrt(n)). That's the root of the largest square in the range [1,n].
And 1 is the smallest root. So you have the roots from 1 to R, that's R roots.
Which correspond to the R squares. So int(sqrt(n)) is the answer. */

class Solution {
public:
    int bulbSwitch(int n) {
        return (int)sqrt(n);
    }
};