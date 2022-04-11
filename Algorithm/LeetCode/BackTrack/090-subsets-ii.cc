/* Medium
Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]


Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10

Relatives:
320. Generalized Abbreviation
784. Letter Case Permutation
1982. Find Array Given Subset Sums
2044. Count Number of Maximum Bitwise-OR Subsets

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
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtrack(nums, 0);

        return _Result;
    }

private:
    void backtrack(const vector<int>& nums, int beg) {
        _Result.push_back(_Track);

        for (int i = beg; i < nums.size(); ++i) {
            if (i == beg || nums[i] != nums[i-1]) {
                _Track.emplace_back(nums[i]);
                backtrack(nums, i + 1);
                _Track.pop_back();
            }
        }
    }

private:
    vector<int> _Track;
    vector<vector<int>> _Result;
};