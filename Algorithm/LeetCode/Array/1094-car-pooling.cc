/* Medium
There is a car with capacity empty seats.
The vehicle only drives east (i.e., it cannot turn around and drive west).

You are given the integer capacity and an array trips where
trip[i] = [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi passengers
and the locations to pick them up and drop them off are fromi and toi respectively.
The locations are given as the number of kilometers due east from the car's initial location.

Return true if it is possible to pick up and drop off all passengers for all the given trips, or false otherwise.

Example 1:
Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false

Example 2:
Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true

Example 3:
Input: trips = [[2,1,5],[3,5,7]], capacity = 3
Output: true

Example 4:
Input: trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = 11
Output: true

Constraints:
1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 10^5

Relatives:
370. Range Addition
598. Range Addition II
1094. Car Pooling
1109. Corporate Flight Bookings */

#include <vector>

using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        for (const auto& trip : trips) {
            Len = max(Len, trip[2] + 1);
            update(trip[1], trip[2], trip[0]);
        }

        auto result = getResult();

        return std::find_if(result.cbegin(), result.cend(), [&capacity](const auto& sum) {
            return sum > capacity;
        }) == result.end();
    }

private:
    void update(int beg, int end, int val) {
        Diff[beg] += val;
        if (end < Diff.size()) {
            Diff[end] -= val;
        }
    }

    vector<int> getResult() const {
        auto result = vector(Diff.begin(), Diff.begin() + Len);

        for (auto i = 1; i < Len; ++i) {
            result[i] += result[i-1];
        }

        return result;
    }

private:
    int Len = 0;
    vector<int> Diff = vector(1001, 0);
};