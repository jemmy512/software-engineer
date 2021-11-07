/* Medium
A conveyor belt has packages that must be shipped from one port to another within `days` days.

The ith package on the conveyor belt has a weight of weights[i].
Each day, we load the ship with packages on the conveyor belt (in the order given by weights).
We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages
on the conveyor belt being shipped within days days.

Example 1:
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

Note that the cargo must be shipped in the order given,
so using a ship of capacity 14 and splitting the packages into parts like
(2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.

Example 2:
Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4

Example 3:
Input: weights = [1,2,3,1,1], days = 4
Output: 3
Explanation:
1st day: 1
2nd day: 2
3rd day: 3
4th day: 1, 1

Constraints:
1 <= days <= weights.length <= 5 * 10^4
1 <= weights[i] <= 500

Relatives:
410. Split Array Largest Sum
1011. Capacity To Ship Packages Within D Days
1231. Divide Chocolate
1891. Cutting Ribbons */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int beg = 1;
        // int end = std::accumulate(weights.cbegin(), weights.cend(), 1);
        int end = 5 * 500 * 10000;

        while (beg < end) {
            auto mid = beg + (end - beg) / 2;
            auto needDays = getDays(weights, mid);

            if (needDays <= days) {
                end = mid;
            } else if (needDays > days) {
                beg = mid + 1;
            }
        }

        return beg;
    }

private:
    int getDays(const vector<int>& weights, const int capacity) {
        auto days = 1;
        auto sum = 0;

        for (auto i = 0; i < weights.size(); ++i) {
            if (sum + weights[i] > capacity) {
                ++days;
                sum = weights[i];
                if (sum > capacity)
                    return INT_MAX;
            } else {
                sum += weights[i];
            }
        }

        return days;
    }

    int _getDays(const vector<int>& weights, const int capacity) {
        int i = 0;
        int days = 0;

        while (i < weights.size()) {
            int cap = capacity;
            while (i < weights.size()) {
                ++i;
                if (cap < weights[i])
                    break;
                else
                    cap -= weights[i];
            }
            ++days;
        }

        return days;
    }
};