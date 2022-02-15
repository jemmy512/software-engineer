/*
Difficulty: Medium

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note:
1 is typically treated as an ugly number.
n does not exceed 1690.

Relatives:
263. Ugly Number
264. Ugly Number II
1201. Ugly Number III
023. Merge k Sorted Lists
204. Count Primes
279. Perfect Squares
313. Super Ugly Number */

/* The idea is we generate the ugly number instead of checking every number.
 *
 * To generate the next ugly number, we can use the existed ugly numbers to multiply 2,3,5,
 * and get the minimal one.
 *
 *     Let's start from the first ugly number - [1]
 *
 *        [1]  next = min( 1*2=2, 1*3=3, 1*5=5) = 2
 *
 *     Now we have [1,2], we can see, only the second one need be multipied by 2
 *     but both 3 and 5 still need be multipied by first one. So:
 *
 *        [1,2]  next = min(2*2=4, 1*3=3, 1*5=5) = 3
 *
 *     Now we have [1,2,3], we can see the second one need be mulityped by 2 and 3,
 *     but the 5 still needs be multipied by first one. So:
 *
 *        [1,2,3]  next = min (2*2, 2*3, 1*5) = 4
 *
 *     and so on...
 *
 * So, we can see we need to maintain three indics in ugly number list,
 * each one represents the place need be mulipied by 2,3,5.
 *
 * And we increase the index who's multiplication is the minimal.
 *
 * Be careful about the cases such as 6, in which we need to forward both pointers of 2 and 3. */

#include <vector>
#include <algorithm>

using std::vector;
using std::min;

class Solution {
public:
    int nthUglyNumber(int n) {
        if (n < 0) return 0;

        std::vector<int> ugly(n, 0);
        ugly[0] = 1;
        int i2 = 0, i3 = 0, i5 = 0;

        for (int i = 1; i < n; ++i) {
            auto m2 = ugly[i2]*2;
            auto m3 = ugly[i3]*3;
            auto m5 = ugly[i5]*5;

            ugly[i] = std::min({m2, m3, m5});

            if (ugly[i] == m2) ++i2;
            if (ugly[i] == m3) ++i3;
            if (ugly[i] == m5) ++i5;
        }

        return ugly[n-1];
    }
};