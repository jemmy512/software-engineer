/* Hard
Given an unsorted integer array nums, find the smallest missing positive integer.

Example 1:
Input: nums = [1,2,0]
Output: 3

Example 2:
Input: nums = [3,4,-1,1]
Output: 2

Example 3:
Input: nums = [7,8,9,11,12]
Output: 1

Constraints:
0 <= nums.length <= 300
-2^31 <= nums[i] <= 2^31 - 1 

Relatives:
041. First Missing Positive
268. Missing Number 
287. Find the Duplicate Number 
448. Find All Numbers Disappeared in an Array 
765. Couples Holding Hands */

/*
 *  Idea:
 *
 *    We can move the num to the place whcih the index is the num.
 *
 *    for example,  (considering the array is zero-based.
 *       1 => A[0], 2 => A[1], 3=>A[2]
 *
 *    Then, we can go through the array check the i+1 == A[i], if not ,just return i+1;
 *
 *    This solution comes from StackOverflow.com
 *    http://stackoverflow.com/questions/1586858/find-the-smallest-integer-not-in-a-list
*/

#include <vector>
#include <utility>

using namespace std;

int firstMissingPositive_move(vector<int>& nums) {
    if (nums.empty())
        return 1;

    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] > 0 && nums[i] < nums.size() && nums[nums[i]-1] != nums[i]) {
            swap(nums[i], nums[nums[i]-1]);
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (i+1 != nums[i]){
            return i+1;
        }
    }

    return nums.size()+1;
}

/*
 *    The idea is simple:
 *
 *    1) put all of number into a map.
 *    2) for each number a[i] in array, remove its continous number in the map
 *        2.1)  remove ... a[i]-3, a[i]-2, a[i]-1, a[i]
 *        2.2)  remove a[i]+1, a[i]+2, a[i]+3,...
 *    3) during the removeing process, if some number cannot be found, which means it's missed.
 *
 *    considering a case [-2, -1, 4,5,6],
 *        [-2, -1] => missed 0
 *        [4,5,6]  => missed 3
 *
 *    However, we missed 1, so, we have to add dummy number 0 whatever.
 *
 *    NOTE: this solution is not constant space slution!!!!
 *
 */
int firstMissingPositive_map(int A[], int n) {
    map<int, int> cache;
    for(int i = 0; i < n; i++){
        cache[A[i]] = i;
    }

    //add dummy
    if (cache.find(0) == cache.end() ) {
        cache[0] = -1;
    }

    int miss = INT_MAX;
    int x;
    for (int i = -1; i < n && cache.size() > 0; i++){

        if (i == -1){
            x = 0; //checking dummy
        }else{
            x = A[i];
        }

        if (cache.find(x) == cache.end()){
            continue;
        }

        int num ;
        // remove the ... x-3, x-2, x-1, x
        for( num = x; cache.find(num) != cache.end(); num--){
            cache.erase(cache.find(num));
        }
        if ( num > 0 && num < miss  ){
            miss = num;
        }
        // remove the x+1, x+2, x+3 ...
        for ( num = x+1; cache.find(num) != cache.end(); num++){
            cache.erase(cache.find(num));
        }
        if ( num > 0 && num < miss) {
            miss = num;
        }
    }
    return miss;
}