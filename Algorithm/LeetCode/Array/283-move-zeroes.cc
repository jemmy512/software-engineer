/* Easy
Given an array nums, write a function to move
all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12],
after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

Constraints:
1 <= nums.length <= 10^4
-2^31 <= nums[i] <= 2^31 - 1

Relatives:
019. Remove Nth Node From End of List
027. Remove Element
026. Remove Duplicates from Sorted Array
080. Remove Duplicates from Sorted Array II
083. Remove Duplicates from Sorted List
082. Remove Duplicates from Sorted List II 
203. Remove Linked List Elements
237. Delete Node In A Linked List
283. Move Zeroes
1474. Delete N Nodes After M Nodes of a Linked List
1721. Swapping Nodes in a Linked List 
1836. Remove Duplicates From an Unsorted Linked List */

#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int firstZeroPos = 0, curPos = 0; curPos < nums.size(); ++curPos) {
            if (nums[curPos] != 0) {
                swap(nums[firstZeroPos++], nums[curPos]);
            }
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int pos = 0;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                nums[pos++] = nums[i];
            }
        }

        std::fill(nums.begin()+pos, nums.end(), 0);
    }
};