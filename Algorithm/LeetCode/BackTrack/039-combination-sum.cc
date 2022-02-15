/* Medium
Given an array of distinct integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers remain to target.
You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times.
Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that remain up to target
is less than 150 combinations for the given input.


Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []

Example 4:
Input: candidates = [1], target = 1
Output: [[1]]

Example 5:
Input: candidates = [1], target = 2
Output: [[1,1]]

Constraints:
1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500

Relatives:
017. Letter Combinations of a Phone Number
039. Combination Sum
040. Combination Sum II
216. Combination Sum III
377. Combination Sum IV

078. Subsets
090. Subsets II */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, 0, target);

        return Result;
    }

private:
    void backtrack(const vector<int>& candidates, int i, int remain) {
        if (remain < 0) {
            return;
        }

        if (remain == 0) {
            Result.emplace_back(Track);
            return;
        }

        for (; i < candidates.size(); ++i) {
            remain -= candidates[i];
            Track.emplace_back(candidates[i]);

            backtrack(candidates, i, remain);

            remain += candidates[i];
            Track.pop_back();
        }
    }

private:
    vector<int> Track;
    vector<vector<int>> Result;
};