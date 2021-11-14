/* Medium
There are n cities connected by some number of flights. You are given an array flights
where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops.
If there is no such route, return -1.

Example 1:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation: The graph is shown.
The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.

Example 2:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation: The graph is shown.
The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.


Constraints:
1 <= n <= 100
0 <= flights.length <= (n * (n - 1) / 2)
flights[i].length == 3
0 <= fromi, toi < n
fromi != toi
1 <= pricei <= 104
There will not be any multiple flights between two cities.
0 <= src, dst, k < n
src != dst */

#include <vector>
#include <map>
#include <utility>

using namespace std;

// top down
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        ++k;
        Src = src;
        Memo.resize(n, vector(k+1, -1));

        for (const auto& f : flights) {
            Indegree[f[1]].emplace_back(f[0], f[2]);
        }

        return dp(dst, k);
   }

private:
    int dp(int pos, int k) {
        if (pos == Src)
            return 0;
        if (k == 0)
            return -1;
        if (Memo[pos][k] != -1)
            return Memo[pos][k];

        auto ret = INT_MAX;

        if (Indegree.find(pos) != Indegree.end()) {
            for (const auto& [from, price] : Indegree[pos]) {
                auto subproblem = dp(from, k - 1);
                if (subproblem != -1) {
                    ret = min(ret, subproblem + price);
                }
            }
        }

        Memo[pos][k] = ret == INT_MAX ? -1 : ret;

        return Memo[pos][k];
    }

private:
    int Src{0};
    vector<vector<int>> Memo; //the price from src to pos
    map<int, vector<pair<int, int>>> Indegree;
};

// bottom up
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        Dst = dst;
        Memo.resize(n, vector(k+1, -1));

        for (const auto& f : flights) {
            Outdegree[f[0]].emplace_back(f[1], f[2]);
        }

        auto ret = dp(src, k);

        return ret == INT_MAX ? -1 : ret;
    }

private:
    int dp(int from, int to, int k) {
        if (to == Dst)
            return 0;

        if (k < 0)
            return -1;

        if (Memo[from][to] != -1)
            return Memo[from][to];

        auto ret = INT_MAX;

        if (Outdegree.find(to) != Outdegree.end()) {
            for (const auto& [next, price] : Outdegree[to]) {
                auto subproblem = dp(to, next, k - 1);
                if (subproblem != -1) {
                    ret = min(ret, subproblem + price);
                }
            }
        }

        Memo[from][to] = ret == INT_MAX ? -1 : ret;

        return Memo[from][to];
    }

private:
    int Dst{0};
    vector<vector<int>> Memo;
    map<int, vector<pair<int, int>>> Outdegree;
};