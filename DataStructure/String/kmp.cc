/*
 * Created by Jemmy on 2018/8/4.
 *
 */
#include <iostream>
#include <string>
using namespace std;

int *getNext(const string &ps) {
    const int len = ps.size();
    int i, j, k;
    int *next = new int[len];
    k = -1;
    next[0] = -1;
    for (i = 0; i < len;) {
        if (k == -1 || ps[i] == ps[k]) {
            ++i;
            ++k;
            if (ps[i] == ps[k]) {
                next[i] = next[k];
            } else {
                next[i] = k;
            }
        } else {
            k = next[k];
        }
    }
    cout << "next[";
    for (int i = 0; i < len; ++i) {
        cout << next[i] << ", ";
    }
    cout << endl;
    return next;
}

int kmp(const string &ts, const string &ps) {
    int lenT = ts.size();
    int lenP = ps.size();
    int i = 0, j = 0;
    int *next = getNext(ps);
    while (i < lenT && j < lenP) {
        if (j == -1 || ts[i] == ps[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }

    delete next;
    if (j == lenP)
        return i - j;
    return -1;
}

int main() {
    string ts = "abcdabcevf";
    string ps = "aaacaabv";
    cout << "index of patter: " << kmp(ts, ps) << endl;
}
