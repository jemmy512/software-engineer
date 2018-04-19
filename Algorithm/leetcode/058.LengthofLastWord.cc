/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

Example:

Input: "Hello World"
Output: 5
*/

int lengthOfLastWord(string s) {
    int count = 0;
    int i;
    for (i = s.size() - 1; s[i] == ' '; --i);
    while (i >=0 && s[i--] != ' ') ++count;
    
    return count;
}