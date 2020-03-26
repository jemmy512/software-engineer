/*
 * Created by by on 2018/8/13.
 * Ref: https://segmentfault.com/a/1190000002710424
 */
#include <iostream>
#include <string>

using namespace std;

void stringCombination(const string & str) {
    int len = str.size();
    int n = 1<<len;
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < len; ++j) {
            int tmp = i;
            if (tmp & (1<<j))
                cout << str[j];
        }
        cout << endl;
    }
}

int main() {
    string str = "abc";
    stringCombination(str);
}


