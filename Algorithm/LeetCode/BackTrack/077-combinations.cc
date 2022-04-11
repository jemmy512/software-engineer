/* Medium
Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].
You may return the answer in any order.

Example 1:
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

Example 2:
Input: n = 1, k = 1
Output: [[1]]

Constraints:
1 <= n <= 20
1 <= k <= n

Relatives:
078. Subsets
090. Subsets II

046. Permutations
047. Permutations II

077. Combinations
039. Combination Sum
040. Combination Sum II
216. Combination Sum III
377. Combination Sum IV */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        Track.reserve(k);
        backtrack(n, k, 1);

        return Result;
    }

private:
    void backtrack(int n, int k, int beg) {
        if (k == Track.size()) {
            Result.emplace_back(Track);
        } else {
            for (auto i = beg; i <= n; ++i) {
                Track.emplace_back(i);
                backtrack(n, k, i + 1);
                Track.pop_back();
            }
        }
    }

private:
    vector<int> Track;
    vector<vector<int>> Result;
};