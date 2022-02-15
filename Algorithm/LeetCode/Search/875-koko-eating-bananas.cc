/* Medium
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas.
The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour,
she chooses some pile of bananas and eats k bananas from that pile.
If the pile has less than k bananas,
she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23


Constraints:
1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9 */

#include <vector>

using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int beg = 1;
        int end = 1000000000 + 1;

        while (beg < end) {
            auto mid = beg + (end - beg) / 2;
            auto time = eatingTime(piles, mid);

            if (time <= h) {
                end = mid;
            } else {
                beg = mid + 1;
            }
        }

        return beg;
    }

private:
    int eatingTime(const vector<int>& piles, int speed) {
        int hours = 0;

        for (auto i = 0; i < piles.size(); ++i) {
            hours += piles[i] / speed;
            hours += piles[i] % speed > 0 ? 1 : 0;
        }

        return hours;
    }
};