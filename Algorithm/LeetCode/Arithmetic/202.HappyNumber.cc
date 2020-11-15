/* Easy

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer,
replace the number by the sum of the squares of its digits, and repeat the process
until the number equals 1 (where it will stay),
or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1 */

#include <iostream>
#include <unordered_set>

using namespace std;

// 401 test cases, 4ms, beat 85.26%
class Solution {
public:
    static int squareSum(int n) {
        int sum = 0;

        while (n > 0) {
            int remainder = n % 10;
            sum += remainder * remainder;
            n /= 10;
        }

        return sum;
    }

    static bool isHappy(int n) {
        if (n < 0)
            return false;

        std::unordered_set<int> uset;
        while (n != 1 && uset.find(n) == uset.end()) {
            uset.insert(n);
            n = squareSum(n);
        }

        return n == 1;
    }
};

int main() {
    cout << Solution::isHappy(19) << endl;
}