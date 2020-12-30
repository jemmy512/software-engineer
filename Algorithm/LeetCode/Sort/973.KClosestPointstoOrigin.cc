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
-10000 < points[i][1] < 10000 */

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
    Iter partition(Iter begin, Iter end, Compare cmp) { // [begin, end}
        end = std::next(end, -1);
        auto pivotIter = std::next(begin, getRandom<int>(std::distance(begin, end)));
        auto pivot = *pivotIter;
        std:swap(*begin, *pivotIter);

        while (begin < end) {
            while (begin < end && cmp(pivot, *end))
                --end;
            if (begin < end)
                *begin++ = *end;
            while (begin < end && cmp(*begin, pivot))
                ++begin;
            if (begin < end)
                *end-- = *begin;
        }
        *begin = pivot;

        return begin;
    }

    template<typename sizeT>
    sizeT getRandom(sizeT maxSize, double probability = 0.5) {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        auto engine = std::default_random_engine(seed);
        auto distribution = std::binomial_distribution<sizeT>(maxSize, probability);

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