/* Easy
Given an array nums and a value val, remove all instances of that value in-place and return the new length.

Do not allocate extra space for another array,
you must do this by modifying the input array in-place with O(1) extra memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example 1:
Given nums = [3,2,2,3], val = 3,
Your function should return length = 2, with the first two elements of nums being 2.
It doesn't matter what you leave beyond the returned length.

Example 2:
Given nums = [0,1,2,2,3,0,4,2], val = 2,
Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.
Note that the order of those five elements can be arbitrary.

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

#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& nums, int val) {
    int pos = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {
            nums[pos++] = nums[i];
        }
    }

    return pos;
}

int removeElement(vector<int>& nums, int val) {
    int i = 0;
    int j = nums.size()-1;

    while (i <= j) {
        while (i < nums.size() && nums[i] != val)
            ++i;
        while (j >= 0 && nums[j] == val)
            --j;
        if (i < j)
            swap(nums[i++], nums[j--]);
    }

    return i;
}

int removeElement(vector<int>& nums, int val) {
    int i = 0;
    int len = nums.size();

    while (i < len) {
        if (nums[i] == val) {
            nums[i] = nums[--len];
        } else {
            ++i;
        }
    }

    return len;
}