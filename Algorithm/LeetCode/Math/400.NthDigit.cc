/* Medium
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0,
which is part of the number 10. */

/* We can see the following pattern:
 * 1, 2, .... 9 : there are 9 * 1 digits.
 * 10, 11, ..., 99: there are 90 * 2 digits.
 * 100, 101, 102, ..., 999:  there are 900 * 3. */

class Solution {
public:
    int findNthDigit(int n) {
        int cycle = 1, startNum = 1;
        long cycle9 = 9; /* cycle * cycle9 may overflow */
        while (n > cycle * cycle9) {
            n -= cycle * cycle9;
            startNum *= 10;
            cycle9 *= 10;
            ++cycle;
        }
        startNum += (n - 1) / cycle;
        return to_string(startNum)[(n - 1) % cycle] - '0';
    }
};

class Solution {
public:
    int findNthDigit(int n) {
        int digit = 1;
        int accu = 0;
        while(true){
            if((n - accu)/(9.0*digit) <= pow(10, digit - 1)) break;
            int digit_num = pow(10, digit - 1) * 9 * digit;
            accu += digit_num;
            digit++;
        }
        n = n - accu;
        int n_num;
        n_num = (n-1) / digit + pow(10, digit-1);
        int n_pos = digit - (n-1)%digit;
        int j = pow(10, n_pos-1);

        return (n_num%(10*j))/j;
    }
};

class Solution {
public:
    int findNthDigit(int n) {
        // step 1. calculate how many digits the number has.
        long base = 9, digits = 1;
        while (n - base * digits > 0)
        {
            n -= base * digits;
            base *= 10;
            digits ++;
        }

        // step 2. calculate what the number is.
        int index = n % digits;
        if (index == 0)
            index = digits;
        long num = 1;
        for (int i = 1; i < digits; i ++)
            num *= 10;
        num += (index == digits) ? n / digits - 1 : n / digits;;

        // step 3. find out which digit in the number is we wanted.
        for (int i = index; i < digits; i ++)
            num /= 10;
        return num % 10;
    }
};