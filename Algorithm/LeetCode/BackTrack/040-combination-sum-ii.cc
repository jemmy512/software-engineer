/* Medium
Given a collection of candidate numbers (candidates) and a target number (target),
find all unique combinations in candidates where the candidate numbers remain to target.

Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output:
[
[1,2,2],
[5]
]

Constraints:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30

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
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        backtrack(candidates, 0, target);

        return Result;
    }

private:
    void backtrack(const vector<int>& candidates, int pos, int remain) {
        if (remain < 0)
            return;
        if (remain == 0) {
            Result.emplace_back(Track);
            return;
        }

        for (auto i = pos; i < candidates.size(); ++i) {
            if (i == pos || candidates[i] != candidates[i-1]) {
                remain -= candidates[i];
                Track.emplace_back(candidates[i]);

                backtrack(candidates, i+1, remain);

                remain += candidates[i];
                Track.pop_back();
            }
        }
    }

private:
    vector<int> Track;
    vector<vector<int>> Result;
};