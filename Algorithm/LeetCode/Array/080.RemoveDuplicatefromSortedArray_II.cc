/* Medium
Given a sorted array nums, remove the duplicates in-place such that
duplicates appeared at most twice and return the new length.

Do not allocate extra space for another array, you must do this
by modifying the input array in-place with O(1) extra memory.

Example 1:
Given nums = [1,1,1,2,2,3],
Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It doesn't matter what you leave beyond the returned length.

Example 2:
Given nums = [0,0,1,1,1,1,2,3,3],
Your function should return length = 7, with the first seven elements of nums being modified
to 0, 0, 1, 1, 2, 3 and 3 respectively.

It doesn't matter what values are set beyond the returned length.
Clarification:
Confused why the returned value is an integer but your answer is an array?
Note that the input array is passed in by reference, which means modification to the
input array will be known to the caller as well.

Internally you can think of this:
// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);
// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}

Constraints:
1 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4

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
    int removeDuplicates(vector<int>& nums) {
        int newIdx = 1;
        int count = 1;

        for (int i = 1; i < nums.size(); ++i) {
            count = (nums[i-1] == nums[i]) ? count + 1 : 1;

            if (count <= 2) {
                nums[newIdx++] = nums[i];
            }
        }

        return newIdx;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size(), duplicate = INT_MIN;
        int index = 0;
        for (int i = 0; i < len;) {
            if (i+1 < len && nums[i] == nums[i+1] && nums[i] != duplicate) {
                duplicate = nums[i];
                nums[index++] = nums[i];
                nums[index++] = nums[i+1];
                i += 2;
            } else {
                if (nums[i] != duplicate)
                    nums[index++] = nums[i];
                ++i;
            }
        }
        return index;
    }
};