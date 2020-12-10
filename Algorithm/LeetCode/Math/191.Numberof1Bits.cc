/*
Write a function that takes an unsigned integer and returns the number of
    ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation
    00000000000000000000000000001011, so the function should return 3.
*/
#include<iostream>
using namespace std;

// 600 test cases, 6ms, beat 71.93%
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n > 0) {
            if (n & 1)
                ++cnt;
            n >>= 1;
        }
        return cnt;
    }

    int hammingWeight_ii(uint32_t n) {
        int cnt = n ? 1 : 0;
        while(n &= (n-1)) cnt++;
        return cnt;
    }
};

int main() {
    Solution sl;
   cout << sl.hammingWeight(11) << endl;
}