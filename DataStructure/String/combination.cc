/*
 * Created by by on 2018/8/13.
 * Ref: https://segmentfault.com/a/1190000002710424
 */
#include <iostream>
#include <string>

using std::string, std::cout, std::endl;

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
