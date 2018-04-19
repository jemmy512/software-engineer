/*
Implement atoi to convert a string to an integer.
Hint: Carefully consider all possible input cases. If you want a challenge, 
    please do not see below and ask yourself what are the possible input cases.
Notes: It is intended for this problem to be specified vaguely (ie, no given input specs).
   You are responsible to gather all the input requirements up front.

Requirements for atoi:
The function first discards as many whitespace characters as necessary until the 
    first non-whitespace character is found. Then, starting from this character,
    takes an optional initial plus or minus sign followed by as many numerical 
    digits as possible, and interprets them as a numerical value.
The string can contain additional characters after those that form the integral 
    number, which are ignored and have no effect on the behavior of this function.
If the first sequence of non-whitespace characters in str is not a valid integral 
    number, or if no such sequence exists because either str is empty or it contains
    only whitespace characters, no conversion is performed.
If no valid conversion could be performed, a zero value is returned. If the correct
    value is out of the range of representable values, 
    INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
    
we only need to handle four cases:
    1. discards all leading whitespaces
    2. sign of the number   
    3. overflow    
    4. invalid input      

*/

#include<stdio.h>
#include<stdlib.h>

int myAtoi(char* str) {
    if (str == NULL || str == '\0')
        return 0;
    
    int ret = 0;
    char *ind = str;
    while (*ind == ' ')
        ++ind;
    int flag = 1;
    if (*ind == '+') {
        ++ind;
    } else if (*ind == '-') {
        flag = 0;
        ++ind;
    }
        
    int tmp;
    while(*ind <= '9' && *ind >= '0') {
        tmp = ret * 10 + *ind - '0';
        if (tmp / 10 != ret)
            return flag ? INT_MAX : INT_MIN;
        ret = tmp;
        ++ind;
    }
    return flag ? ret : -ret;
}

int main() {
    printf("\"%s\" = %d\n", "123", myAtoi("123"));
    printf("\"%s\" = %d\n", "   123", myAtoi("    123"));
    printf("\"%s\" = %d\n", "+123", myAtoi("+123"));
    printf("\"%s\" = %d\n", " -123", myAtoi(" -123"));
    printf("\"%s\" = %d\n", "123ABC", myAtoi("123ABC"));
    printf("\"%s\" = %d\n", " abc123ABC", myAtoi(" abc123ABC"));
    printf("\"%s\" = %d\n", "2147483649", myAtoi("2147483647"));
    printf("\"%s\" = %d\n", "-2147483648", myAtoi("-2147483648"));
    printf("\"%s\" = %d\n", "2147483648", myAtoi("2147483648"));
    printf("\"%s\" = %d\n", "-2147483649", myAtoi("-2147483649"));
}