/* Medium
Given an array, rotate the array to the right by k steps, where k is non-negative.

Follow up:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?

Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints:
1 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5

Follow up:
Try to come up with as many solutions as you can.
There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?

Relatives:
061. Roate List By K
189. Rotate Array
725. Split Linked List in Parts */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& vec, int k) {
        const auto size = vec.size();
        if ((k %= size) == 0) {
            return;
        }

        std::reverse(vec.begin(), vec.end());
        std::reverse(vec.begin(), vec.begin() + k);
        std::reverse(vec.begin() + k, vec.end());
    }
};

class Solution {
public:
    void rotate(vector<int>& vec, int k) {
        int len = vec.size();
        int newK = len - k % len;

        vector vec(vec.begin() + newK, vec.end());
        vec.insert(vec.begin(), vec.begin(), vec.end());
        vec.resize(len);
    }
};

class Solution {
public:
    void rotate(vector<int>& vec, int k) {
        int len = vec.size();
        int newK = k % len;
        int cnt = len - newK;

        while (cnt--) {
            auto beg = vec.begin() + cnt;
            auto end = beg + newK;
            for (;beg != end && end < vec.end(); ++beg) {
                std::swap(*beg, *(beg+1));
            }
        }
    }
};

class Solution {
public:
    void rotate(vector<int>& vec, int k) {
        int newK = k % vec.size();

        while (newK--) {
            for (auto ite = vec.end() - 2; ite >= vec.begin(); --ite) {
                swap(*ite, *(ite + 1));
            }
        }
    }
};

/* Edge case:
[1] 1
[1, 2] 3 */