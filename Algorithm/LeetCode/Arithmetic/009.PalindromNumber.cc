/*
Difficulty: Easy

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?
*/

// 11508 test cases, 138ms, beat 98.90%
static int x=[](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    bool isPalindrome(int x) {
        long tmp = abs(x);
        long reverse = 0;
        
        while (tmp)  {
            reverse = reverse * 10 + (tmp % 10);
            tmp /= 10;
        }
        return reverse == x;
    }
}; 

// 11508 test cases, 270ms, beat 49.55%
class Solution_ {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        vector<int> vec;
        while (x) {
            vec.push_back(x % 10);
            x /= 10;
        }
        
        for (int i = 0, j  = vec.size() - 1; i < j; ++i, --j) {
            if (vec[i] != vec[j])
                return false;
        }
        return true;
    }
};