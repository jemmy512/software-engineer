/* Easy
n an alien language, surprisingly they also use english lowercase letters,
but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.

Given a sequence of words written in the alien language, and the order of the alphabet,
return true if and only if the given words are sorted lexicographicaly in this alien language.

Example 1:
Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.

Example 2:
Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.

Example 3:
Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.)
According to lexicographical rules "apple" > "app", because 'l' > '∅',
where '∅' is defined as the blank character which is less than any other character (More info).


Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are English lowercase letters. */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        _HashMap = buildHashMap(order);

        for (int i = 0; i < words.size()-1; ++i) {
            if (!isLess(words[i], words[i+1])) {
                return false;
            }
        }

        return true;
    }

private:
    bool isLess(const string& lhs, const string& rhs) {
        int len = min(lhs.size(), rhs.size());
        for (int i = 0; i < len; ++i) {
            auto& chL = lhs[i];
            auto& chR = rhs[i];
            if (chL != chR) {
                return _HashMap[chL] < _HashMap[chR];
            }
        }
        return lhs.size() <= rhs.size();
    }

    unordered_map<char, int> buildHashMap(const string& order) {
        unordered_map<char, int> map;
        map.reserve(order.size());

        for (int i = 0; i < order.size(); ++i) {
            map.emplace(order[i], i);
        }

        return map;
    }

private:
    unordered_map<char, int> _HashMap;
};