/* Medium
You are given an integer length and an array updates where updates[i] = [startIdxi, endIdxi, inci].

You have an array arr of length length with all zeros,
and you have some operation to apply on arr.
In the ith operation, you should increment all the elements
arr[startIdxi], arr[startIdxi + 1], ..., arr[endIdxi] by inci.

Return arr after applying all the updates.

Example 1:
Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
Output: [-2,0,3,5,3]

Example 2:
Input: length = 10, updates = [[2,4,6],[5,6,8],[1,9,-4]]
Output: [0,-4,2,2,2,4,4,-4,-4,-4]

Constraints:
1 <= length <= 10^5
0 <= updates.length <= 10^4
0 <= startIdxi <= endIdxi < length
-1000 <= inci <= 1000

Relatives:
370. Range Addition
598. Range Addition II
1094. Car Pooling
1109. Corporate Flight Bookings */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        Diff = vector(length, 0);

        for (const auto& vec : updates) {
            update(vec[0], vec[1], vec[2]);
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

        for (auto i = 1; i < Diff.size(); ++i) {
            result[i] += result[i-1];
        }

        return result;
    }

private:
    vector<int> Diff;
};