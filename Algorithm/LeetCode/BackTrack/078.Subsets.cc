/* Medium
Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.

Relatives:
078. Subsets
090. Subsets II
320. Generalized Abbreviation
784. Letter Case Permutation
1982. Find Array Given Subset Sums
2044. Count Number of Maximum Bitwise-OR Subsets */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0);
        return _Result;
    }

private:
    void backtrack(const vector<int>& nums, int beg) {
        _Result.push_back(_Track);

        for (auto i = beg; i < nums.size(); ++i) {
            _Track.emplace_back(nums[i]);
            backtrack(nums, i + 1);
            _Track.pop_back();
        }
    }

private:
    vector<int> _Track;
    vector<vector<int>> _Result;
};

/* O(N * 2^N)*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        if (nums.empty())
            return {{}};

        const auto num = nums.back();
        nums.pop_back();

        vector<vector<int>> result = subsets(nums);

        const auto size = result.size();
        for (int i = 0; i < size; i++) {
            result.push_back(result[i]);
            result.back().push_back(num);
        }

        return result;
    }
};