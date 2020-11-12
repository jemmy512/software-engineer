/*
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as
    00000010100101000001111010011100), return 964176192 (represented in binary as
    00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

Related problem: Reverse Integer

Performance about remainder and and computing:
    The remainder computing: a Mod b is equivalent to a - (a DIV b ) * b operations.
    The and computing: is a diretive.
*/
#include<iostream>
using namespace std;

// 600 test cases, 4ms, beat 100%
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // 100%
        uint32_t ret = 0, power = 31;
        while (n != 0) {
          ret += (n & 1) << power;
          n = n >> 1;
          power -= 1;
        }

        return ret;
    }

    uint32_t reverseBits(uint32_t n) {
        // /* 6ms, beat 89.90%
        uint32_t ret=0;
        for(int i = 0; i < 32; i++) {
            ret = (ret << 1) + (n & 1);
            n = n >> 1 ;
        }

        return ret;
    }

    uint32_t reverseBits(uint32_t n) {
        uint32_t ret = 0;

        for (int i = 0; i < 32; ++i) {
            ret = ret * 2 + n % 2;
            n /= 2;
        }

        return ret;
    }
};

int main() {
    Solution sl;
    cout << sl.reverseBits(43261596) << endl;

}