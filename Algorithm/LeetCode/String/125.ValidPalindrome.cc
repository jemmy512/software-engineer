 /*
 Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
 */

#include<iostream>
#include<string>
using namespace std;

// passed 476 test cases using 10ms, beat 95.16%
bool isPalindrome(string s) {
    bool result{true};

    int beg = 0;
    int end = s.size()- 1;
    while (beg < end) {
        while (beg < end && !isalnum(s[beg])) ++beg;
        while (beg < end && !isalnum(s[end])) --end;
        if (beg < end && std::toupper(s[beg++]) != std::toupper(s[end--])) {
            result = false;
            break;
        }
    }

    return result;
}

int main() {
    cout << isPalindrome(",.") << endl; // trure
    cout << isPalindrome("0P") << endl; // false
    cout << isPalindrome("A man, a plan, a canal: Panama") << endl;;
}