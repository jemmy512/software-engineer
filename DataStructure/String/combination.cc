/*
 * Created by by on 2018/8/13.
 * Ref: https://segmentfault.com/a/1190000002710424
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Given n and k, return the combination of k numbers from [1, ..., n] */
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (n <= 0 || k <= 0)
            return _Result;

        backtrack(n, k, 1);

        return _Result;
    }

private:
    void backtrack(int n, int k, int beg) {
        if (_Track.size() == k) {
            _Result.push_back(_Track);
        } else {
            for (auto i = beg; i <= n; ++i) {
                _Track.emplace_back(i);
                backtrack(n, k, i + 1);
                _Track.pop_back();
            }
        }
    }

private:
    vector<int> _Track;
    vector<vector<int>> _Result;
};


void stringCombination(const string& str) {
    int n = 1 << str.size();
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < str.size(); ++j) {
            if (i & (1<<j))
                cout << str[j];
        }
        cout << endl;
    }
}

int main() {
    string str = "abc";
    stringCombination(str);
}
