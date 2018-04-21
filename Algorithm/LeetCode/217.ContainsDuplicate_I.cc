/*
Given an array of integers, find if the array contains any duplicates. 
Your function should return true if any value appears at least twice in the array,
 and it should return false if every element is distinct.
*/

#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

// 18/18 test cases, 37ms, beat 80.37%
class Solution {
public:
    static bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> set;
        for (int i : nums) {
            if (set.count(i)) return true;
            set.insert(i);
        }
        /*
        * // 39ms, beat 42.03%
        * // unordered_set is faster than set
        * set<int> set;
        * for (int i : set) {
        *   if (!set.insert(i).second)
        *    return true;
        * }
        */
        
        return false;
    }
};

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << Solution::containsDuplicate(vec);
    return 0;
}