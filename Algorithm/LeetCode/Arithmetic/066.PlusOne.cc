/*
Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.
*/
#include<iostream>
#include<vector>
using namespace std;

// beats 99.68%, 99.68%, 99.68% submissions
vector<int> plusOne(vector<int>& digits) {
    int len = digits.size();
    bool carry = true;
    
    for (int i = len - 1; i >=0 && carry; --i)
        carry = (++digits[i] %= 10) == 0;
    if (carry)
        digits.insert(digits.begin(), 1);
    return digits;
}

// beats 99.68%, 99.68%, 99.68% submissions
vector<int> plusOne_1(vector<int>& digits) {
    if (digits.empty()) {
        digits.push_back(1);
        return digits;
    }
    
    digits.push_back(0);
    int len = digits.size();
    int i = len - 1;
    int x = 0;
    ++digits[i - 1];
    for (; i != 0; --i) {
        x = digits[i - 1] += x;
        digits[i] = x % 10;
        x /= 10;
    }
    if (x)
        digits[0] = x;
    else 
        digits.erase(digits.begin());
    return digits;
}

int main() {
    cout << 10 % 10 << endl;
    
    return 0;
}