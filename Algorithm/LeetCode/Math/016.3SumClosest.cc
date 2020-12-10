/* Medium
Given an array nums of n integers and an integer target, find three integers
    in nums such that the sum is closest to target. Return the sum of the three
    integers. You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
#include<iostream>
#include<climits>
#include<algorithm>
#include<vector>
#include<iterator>
using namespace std;

//solution:  http://en.wikipedia.org/wiki/3SUM
//the idea as blow:
//  1) sort the array.
//  2) take the element one by one, calculate the two numbers in reset array.
//
//notes: be careful the duplication number.
//
// for example:
//    [-4,-1,-1,1,2]    target=1
//
//    take -4, can cacluate the "two number problem" of the reset array [-1,-1,1,2] while target=5
//    [(-4),-1,-1,1,2]  target=5  distance=4
//           ^      ^
//    because the -1+2 = 1 which < 5, then move the `low` pointer(skip the duplication)
//    [(-4),-1,-1,1,2]  target=5  distance=2
//                ^ ^
//    take -1(skip the duplication), can cacluate the "two number problem" of the reset array [1,2] while target=2
//    [-4,-1,(-1),1,2]  target=2  distance=1
//

// 125/125 test cases, 10ms, beat  89.25%
class Solution {
public:
    static int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        int distance = INT_MAX;
        for (int i = 0; i < len-2; ++i) {
            int low = i + 1;
            int high = len - 1;
            while (low < high) {
                int sum = nums[i] + nums[low] + nums[high];
                if (sum == target)
                    return target;
                else {
                    if (abs(target - sum) < abs(distance)) {
                        distance = target - sum;
                    }

                    if (sum > target) {
                        --high;
                    } else {
                        ++low;
                    }
                }
            }
        }

        return target - distance;
    }
};

int main() {
    // vector<int> vec = {1,2,4,8,16,32,64,128};
    vector<int> vec = {1, 1, -1, -1, 3};
    cout << Solution::threeSumClosest(vec, 2) << endl;
}