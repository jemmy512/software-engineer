/* Medium
We have a list of points on the plane. Find the K closest points to the origin (0, 0).
(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.
The answer is guaranteed to be unique (except for the order that it is in.)

Example 1:
Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].

Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

Note:
1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000

Relatives:
215. Kth Largest Element in an Array
324. Wiggle Sort II
347. Top K Frequent Elements
414. Third Maximum Number
703. Kth Largest Element in a Stream
973. K Closest Points to Origin
1985. Find the Kth Largest Integer in the Array */

#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

/* Quick Select
 * Time complexity: O(N), worst O(N^2) */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        quickSelect(points.begin(), points.end(), K, [](const auto& lhs, const auto& rhs) {
            return (lhs[0] * lhs[0] + lhs[1] * lhs[1]) < (rhs[0] * rhs[0] + rhs[1] * rhs[1]);
        });

        points.resize(K);
        return points;
    }

private:
    template<typename Iter, typename Compare>
    void quickSelect(Iter begin, Iter end, int k, Compare cmp) { // [begin, end}
        if (begin + 1 >= end)
            return;

        auto pivot = partition(begin, end, cmp);
        auto dis = std::distance(begin, pivot);
        if (dis == k) {
            return;
        } else if (dis > k) {
            quickSelect(begin, pivot, k, cmp);
        } else {
            quickSelect(pivot, end, k - dis, cmp);
        }
    }

    template<typename Iter, typename Compare>
    Iter partition(Iter begin, Iter end, Compare cmp) {
        --end;
        auto pivot = *std::next(begin, getRandom<int>(0, std::distance(begin, end)));

        while (begin <= end) {
            while (cmp(*begin, pivot))
                ++begin;
            while (cmp(pivot, *end))
                --end;
            if (begin <= end)
                std::swap(*begin++, *end--);
        }

        return begin;
    }

    template<typename Size = int>
    Size getRandom(Size min, Size max) {
        std::random_device dev;
        std::default_random_engine engine(dev());
        std::uniform_int_distribution<Size> distribution(min, max);

        return distribution(engine);
    }
};

/* heap sort
 * Time complexity: heap sort O(NlogN) */
class Solution_ {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto comparator = [](const auto& lhs, auto& rhs){
            return (lhs[0] * lhs[0] + lhs[1] * lhs[1]) > (rhs[0] * rhs[0] + rhs[1] * rhs[1]);
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comparator)> priQue(comparator);

        for (const auto& point : points) {
            priQue.emplace(point);
        }

        vector<vector<int>> result;
        result.reserve(K);

        while (K--) {
            result.emplace_back(priQue.top());
            priQue.pop();
        }

        return result;
    }
};

int main() {
    Solution s;
    vector<vector<int>> points{{{0,1},{1,0}}};
    for (const auto& d : s.kClosest(points, 2)) {
        for (const auto& da : d) {
            std::cout << da << " ";
        }
        std::cout << std::endl;
    }
}