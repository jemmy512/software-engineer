/* Medium
There are n flights that are labeled from 1 to n.

You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi]
represents a booking for flights firsti through lasti (inclusive)
with seatsi seats reserved for each flight in the range.

Return an array answer of length n, where answer[i] is the total number of seats reserved for flight i.

Example 1:
Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]
Explanation:
Flight labels:        1   2   3   4   5
Booking 1 reserved:  10  10
Booking 2 reserved:      20  20
Booking 3 reserved:      25  25  25  25
Total seats:         10  55  45  25  25
Hence, answer = [10,55,45,25,25]

Example 2:
Input: bookings = [[1,2,10],[2,2,15]], n = 2
Output: [10,25]
Explanation:
Flight labels:        1   2
Booking 1 reserved:  10  10
Booking 2 reserved:      15
Total seats:         10  25
Hence, answer = [10,25]

Constraints:
1 <= n <= 2 * 10^4
1 <= bookings.length <= 2 * 10^4
bookings[i].length == 3
1 <= firsti <= lasti <= n
1 <= seatsi <= 10^4

Relatives:
370. Range Addition
598. Range Addition II
1094. Car Pooling
1109. Corporate Flight Bookings */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        Diff = vector(n, 0);

        for (const auto& vec : bookings) {
            update(vec[0]-1, vec[1]-1, vec[2]);
        }

        return getResult();
    }

private:
    void update(int beg, int end, int val) {
        Diff[beg] += val;
        if (end + 1 < Diff.size()) {
            Diff[end+1] -= val;
        }
    }

    vector<int> getResult() const {
        auto result = Diff;

        for (auto i = 1 ; i < Diff.size(); ++i) {
            result[i] += result[i-1];
        }

        return result;
    }

private:
    vector<int> Diff;
};