/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell
 one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

/* Solution:
Ref: https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm

The logic to solve this problem is same as "max subarray problem" using Kadane's Algorithm.

All the straight forward solution should work, but if the interviewer twists the question
 slightly by giving the difference array of prices, Ex: for {1, 7, 4, 11}, if he gives {0, 6, -3, 7},
 you might end up being confused.

Here, the logic is to calculate the difference (maxCur += prices[i] - prices[i-1]) of the original 
array, and find a contiguous subarray giving maximum profit. If the difference falls below 0, reset it to zero.
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        
        int maxRet = 0, maxCur = 0;
        for (int i = 1; i < len; ++i) {
            maxCur = max(0, maxCur += prices[i] - prices[i-1]);
            maxRet = max(maxRet, maxCur);
        }
        
        return maxRet;
    }
};