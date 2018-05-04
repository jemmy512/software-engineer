/*
Given an arbitrary ransom note string and another string containing 
letters from all the magazines, write a function that will return true 
if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true

*/

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size())
            return false;
        
        int ascii[128] = {0};
        int len = magazine.size();
        for (int i = 0; i < len; ++i) {
            ++ascii[magazine[i]];
        }
        
        len = ransomNote.size();
        for (int i = 0; i < len; ++i) {
            if (--ascii[ransomNote[i]] < 0)
                return false;
        }
        return true;
    }
};

