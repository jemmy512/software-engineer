/*Difficulty: Easy

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

Coud you solve it without converting the integer to a string? */

class Solution {
public:
    /* Revert half of the number */
    bool isPalindrome(int x) {
        /* When x < 0, x is not a palindrome.
         * Also if the last digit of the number is 0, in order to be a palindrome,
         * the first digit of the number also needs to be 0.
         * Only 0 satisfy this property. */
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + (x % 10);
            x /= 10;
        }

        /* When the length is an odd number, we can get rid of the middle digit by reverse/10
         * E.g., 12321, at the end of the while loop we get x = 12, reverse = 123,
         * since the middle digit doesn't matter in palidrome(it will always equal to itself),
         * we can simply get rid of it. */
        return x == reverse || x == reverse/10;
    }

    /* Revert whole number */
    bool isPanlindrom_i(int x) {
        long tmp = abs(x);
        long reverse = 0;

        while (tmp)  {
            reverse = reverse * 10 + (tmp % 10);
            tmp /= 10;
        }

        return x == reverse;
    }

    bool isPalindrome_ii(int x) {
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