/* Easy
The next greater element of some element x in an array is
the first greater element that is to the right of x in the same array.

You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.

For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j]
and determine the next greater element of nums2[j] in nums2.
If there is no next greater element, then the answer for this query is -1.

Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.


Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.


Constraints:
1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 10^4
All integers in nums1 and nums2 are unique.
All the integers of nums1 also appear in nums2.

Follow up: Could you find an O(nums1.length + nums2.length) solution?

Relatives:
316. Remove Duplicate Letters
496. Next Greater Element I
503. Next Greater Element II
556. Next Greater Element III
739. Daily Temperatures */

#include <vector>
#include <stack>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        map<int, int> hashMap;
        stack<int> stk;
        vector<int> greater(nums2.size(), -1);
        vector<int> result(nums1.size(), -1);

        for (auto i = 0; i < nums2.size(); ++i) {
            hashMap.emplace(nums2[i], i);
        }

        for (int i = nums2.size()-1; i >= 0; --i) {
            while (!stk.empty() && stk.top() <= nums2[i]) {
                stk.pop();
            }

            greater[i] = stk.empty() ? -1 : stk.top();
            stk.emplace(nums2[i]);
        }

        for (auto i = 0; i < nums1.size(); ++i) {
            result[i] = greater[hashMap[nums1[i]]];
        }

        return result;
    }
};