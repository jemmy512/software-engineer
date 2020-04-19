/*
Difficulty: Medium

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:  

1 is typically treated as an ugly number.
n does not exceed 1690.
*/

    // The idea is we generate the ugly number instead of checking every number.
    //
    // To generate the next ugly number, we can use the existed ugly numbers to multipy 2,3,5,
    // and get the minimal one.
    //
    //     Let's start from the first ugly number - [1]
    //
    //        [1]  next = min( 1*2=2, 1*3=3, 1*5=5) = 2
    //
    //     Now we have [1,2], we can see, only the second one need be multipied by 2
    //     but both 3 and 5 still need be multipied by first one. So:
    // 
    //        [1,2]  next = min(2*2=4, 1*3=3, 1*5=5) = 3
    //
    //     Now we have [1,2,3], we can see the second one need be mulityped by 2 and 3,
    //     but the 5 still needs be multipied by first one. So:
    //
    //        [1,2,3]  next = min (2*2, 2*3, 1*5) = 4
    //
    //     and so on...
    //
    // So, we can see we need to maintain three indics in ugly number list, 
    // each one represents the place need be mulipied by 2,3,5.
    //
    // And we increase the index who's multiplication is the minimal. 
    //

class Solution {
public:
    int nthUglyNumber(int n) {
        if (n < 1) return 0;
        
        vector<int> vec(n);
        vec[0] = 1;
        int t2 = 0, t3 = 0, t5 = 0;
        
        for (int i = 1; i < n; ++i) {
            vec[i] = min(min(vec[t2] * 2, vec[t3] * 3), vec[t5] * 5);
            if (vec[i] == vec[t2] * 2) ++t2;
            if (vec[i] == vec[t3] * 3) ++t3;
            if (vec[i] == vec[t5] * 5) ++t5;
        }
        
        return vec[n - 1];
    }
};