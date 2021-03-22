/*
Given an array of positive integers and a number x, (may dulicate)
find the number of pairs of integers in the array whose XOR is equal to x.

Examples:
Input : arr[] = {5, 4, 10, 15, 7, 6}, x = 5
Output : 1
Explanation :  (10 ^ 15) = 5

Input : arr[] = {3, 6, 8, 10, 15, 50}, x = 5
Output : 2
Explanation : (3 ^ 6) = 5 and (10 ^ 15) = 5

Note: An efficient solution of this problem take O(n) time.
The idea is based on the fact that arr[i] ^ arr[j] is equal to x if and only if arr[i] ^ x is equal to arr[j].
1) Initialize result as 0.
2) Create an empty hash set "s".
3) Do following for each element arr[i] in arr[]
   (a) If x ^ arr[i] is in "s", then increment result by 1.
   (b) Insert arr[i] into the hash set "s".
3) return result.

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs
1803. Count Pairs with XOR in a Range
count All Pairs with given XOR */

#include <vector>
#include <unordered_map>

using namespace std;

int xorPairCount(vector<int> nums, int x) {
    int cnt = 0;
    unordered_map<int, int> hashMap;

    for (const auto& num : nums) {
        int xOr = x^num;
        if (hashMap.find(xOr) != hashMap.end()) {
            cnt += hashMap[xOr];

        }
        ++hashMap[num];
    }

    return cnt;
}