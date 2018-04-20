/*
Given an integer n, return the number of trailing zeroes in (n!).

Note: Your solution should be in logarithmic time complexity.

Credits:
Special thanks to @ts for adding this problem and creating all test cases.
*/
#include<iostream>
using namespace std;

class Solution {
public:
    static int trailingZeroes(int n) {
        int cnt = 0;
        while (n % 10 == 0) {
            ++cnt;
            n /= 10;
        }
        
        return cnt;
    }
};

int main() {
    cout << Solution::trailingZeroes(101) << endl;
}