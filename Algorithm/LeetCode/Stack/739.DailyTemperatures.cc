/* Medium
Given an array of integers temperatures represents the daily temperatures,
return an array answer such that answer[i] is the number of days you have to wait
after the ith day to get a warmer temperature.
If there is no future day for which this is possible, keep answer[i] == 0 instead.


Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:
Input: temperatures = [30,60,90]
Output: [1,1,0]

Constraints:
1 <= temperatures.length <= 10^5
30 <= temperatures[i] <= 100

Relatives:
316. Remove Duplicate Letters
496. Next Greater Element I
503. Next Greater Element II
556. Next Greater Element III
739. Daily Temperatures */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> stk;
        vector<int> result(temperatures.size(), 0);

        for (int i = temperatures.size()-1; i >= 0; --i) {
            while (!stk.empty() && temperatures[stk.top()] <= temperatures[i]) {
                stk.pop();
            }
            result[i] = stk.empty() ? 0 : stk.top() - i;
            stk.emplace(i);
        }

        return result;
    }
};