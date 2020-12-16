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
Note that the order of those five elements can be arbitrary. */

#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int> nums, int val) {
    if (nums.empty())
        return 0;

    int len = nums.size();
    int i =0;
    int j = len - 1;
    while (i <= j) {
        while (nums[i] != val && i < len) ++i;
        while (nums[j] == val && j >= 0) --j;
        if (i < j)
            swap(nums[i++], nums[j--]);
    }
    return i;
}

int removeElement(vector<int> nums, int val) {
    int i = 0;
    int n = nums.size();
    while (i < n) {
        if (nums[i] == val) {
            nums[i] = nums[n - 1];
            n--; // reduce array size by one
        } else {
            i++;
        }
    }
    return n;
}

// 26.07%
int removeElement_1(vector<int> &nums, int val) {
    int pos = 0;
    for (int i=0; i<nums.size(); i++){
        if (nums[i] != val)
            nums[pos++] = nums[i];
    }
    return pos;
}

int main() {
    cout << removeElement({3, 2, 2, 3}, 3) << endl;
    cout << removeElement({3, 3}, 3) << endl;
    cout << removeElement({3}, 3) << endl;

    return 0;
}
