/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
*/
#include<iostream>
#include<unordered_set>
using namespace std;

// 401 test cases, 4ms, beat 85.26%
class Solution {
public:
    static int square(int n) {
        int sq, result = 0;
        for (; n > 0; n /= 10) {
            sq = n % 10;
            result += sq * sq;
        }
        return result;
    }
        
    static bool isHappy(int n) {
        if (n < 0) 
            return false;
        unordered_set<int> uset;
        uset.insert(n);
        
        while (n != 1) {
            n = square(n);
//            if (uset.count(n)) // find() has a better performance than count
            if (uset.find(n) != uset.end())
                return false;
            else 
                uset.insert(n);
        }
        return true;
    }
};

int main() {
    cout << Solution::isHappy(19) << endl;
}