/*
 * Created by by on 2018/8/13.
 * Ref: https://segmentfault.com/a/1190000002710424
 */
#include <iostream>
#include <string>

using namespace std;

bool isSwap(const string &str, int beg, int len) {
    for (; beg < len; ++beg) {
        if (str[beg] == str[len])
            return false;
    }
    return true;
}

void stringPermuation(string &str, int beg, int len) {
    if (beg + 1 == len) {
        cout << str << endl;
    } else {
        for (int i = beg; i < len; ++i) {
            if (isSwap(str, beg, i)) {
                swap(str[beg], str[i]);
                stringPermuation(str, beg+1, len);
                swap(str[beg], str[i]);
            }
        }
    }
}

int main() {
    string str = "bbc";
    stringPermuation(str, 0, str.size());
}

