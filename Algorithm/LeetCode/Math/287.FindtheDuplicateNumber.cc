/* Medium
Given an array of integers nums containing n + 1 integers
where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.
Example 1:
Input: nums = [1,3,4,2,2]
Output: 2

Example 2:
Input: nums = [3,1,3,4,2]
Output: 3

Example 3:
Input: nums = [1,1]
Output: 1

Example 4:
Input: nums = [1,1,2]
Output: 1

Constraints:
2 <= n <= 3 * 10^4
nums.length == n + 1
1 <= nums[i] <= n

All the integers in nums appear only once except for precisely one integer which appears two or more times.

Follow up:
How can we prove that at least one duplicate number must exist in nums?
Can you solve the problem without modifying the array nums?
Can you solve the problem using only constant, O(1) extra space?
Can you solve the problem with runtime complexity less than O(n2)?

Hint:
This problem can be transfromed to "Linked List Cycle" problem.
There are two pointers, one goes one step, another goes two steps.

Reference:
https://en.wikipedia.org/wiki/Cycle_detection
https://blog.csdn.net/thestoryofsnow/article/details/6822576

Constraints:
1 <= n <= 10^5
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or `more` times.

Relative:
141. Linked List Cycle
142. Linked List Cycle II

136. Single Number
137. Single Number II
260. Single Number III
268. Missing Number
287. Find the Duplicate Number
389. Find the Difference
645. Set Mismatch */

#include <vector>

using namespace std;

/* Solution 1: Floyd's Tortoise and Hare (Cycle Detection)
 * Solution 2: Sorting
 * Solution 3: Set */
class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        if (nums.size() < 1)
            return -1;

        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        fast = 0;
        while (fast != slow) {
            fast = nums[fast];
            slow = nums[slow];
        }

        return slow;
    }
};
