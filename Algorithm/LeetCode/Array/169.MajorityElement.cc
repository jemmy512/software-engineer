/* Easy
Given an array of size n, find the majority element.
The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Credits:
Special thanks to @ts for adding this problem and creating all test cases.
ou may assume that the array is non-empty and the majority element always exist in the array.

Example 1:
Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/* Boyer-Moore Voting Algorithm Linear Time Majority Vote Algorithm
 * http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html */
int majorityElement(vector<int> &nums) {
    int majority;
    int cnt = 0;

    for (const auto& n : nums) {
        if (cnt == 0) {
            majority = n;
        }
        cnt += (n == majority) ? 1 : -1;
    }

    return majority;
}

int majorityElement(vector<int>& nums) {
    unordered_map<int, int> hashMap;
    int len = nums.size();
    for (int i = 0; i < len; ++i) {
        if (++hashMap[nums[i]] > len / 2)
            return nums[i];
    }
}