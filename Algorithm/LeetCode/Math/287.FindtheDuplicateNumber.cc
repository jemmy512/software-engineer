/* Medium
Given an array nums containing n + 1 integers where each integer is between 1
 and n (inclusive), prove that at least one duplicate number must exist.
 Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be repeated more than once.

Constraints:
2 <= n <= 3 * 104
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.

Hint:
    This problem can be transfromed to "Linked List Cycle" problem.
    There are two pointers, one goes one step, another goes two steps.

    Refer to: https://en.wikipedia.org/wiki/Cycle_detection
        https://blog.csdn.net/thestoryofsnow/article/details/6822576

Relative:
141 linked List Cycle
142 Linked List Cycle II */

/* Approch 1: Floyd's Tortoise and Hare (Cycle Detection) */
class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        if (!(nums.size() > 1))
            return -1;

        int tortoise = nums[0];
        int hare = nums[nums[0]];
        while (tortoise != hare) {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        }

        hare = 0;
        while (hare != tortoise) {
            hare = nums[hare];
            tortoise = nums[tortoise];
        }

        return tortoise;
    }
};

/* Approach 2: Sorting
 * Approach 3: Set */