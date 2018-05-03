/*
Difficulty: Easy

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.
*/

class Solution {
public:
    int getSum(int a, int b) {
        int sum = a;
        
        while (b != 0) {
            sum = a ^ b;        // calculate sum of a and b without thinking the carry 
            b = (a & b) << 1;   // calculate the carry
            a = sum;            // add sum(without carry) and carry
        }
        
        return sum;
    }
};