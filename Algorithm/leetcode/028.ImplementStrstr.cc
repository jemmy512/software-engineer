/*
Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
*/

void getNext(string needle, int *next) {
    const int len = needle.size();
    int i = 0;
    int k = -1;
    next[0] = -1;
    
    while (i < len) {
        if (k == -1 || needle[i] == needle[k]) {
            ++i;
            ++k;
            if (needle[i] == needle[k])
                next[i] = next[k];
            else 
                next[i] = k;
        } else 
            k = next[k];
    }
}

int strStr(string haystack, string needle) {
    if (needle.empty())
        return 0;
    
    const int len1 = haystack.size();
    const int len2 = needle.size();
    int next[len2];
    getNext(needle, next);
    
    int i = 0;
    int j = 0;
    while (i < len1 && j < len2) {
        if (j == -1 || haystack[i] == needle[j]) {
            ++i;
            ++j;
        } else 
            j = next[j];
    }
    
    //delete next;
    if (j == len2)
        return i - j;
    return -1;
    
}