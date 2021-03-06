/* Created by by on 2018/8/13.
 * Ref: https://segmentfault.com/a/1190000002710424 */
#include <iostream>
#include <string>

using namespace std;

bool doSwap(const string &str, int beg, int end) {
    for (; beg < end; ++beg) {
        if (str[beg] == str[end])
            return false;
    }
    return true;
}

void permute(string &str, int beg, int len) {
    if (beg + 1 == len) {
        cout << str << endl;
        return;
    }

    for (int i = beg; i < len; ++i) {
        if (doSwap(str, beg, i)) {
            swap(str[beg], str[i]);
            permute(str, beg+1, len);
            swap(str[beg], str[i]);
        }
    }
}

int main() {
    string str = "bbc";
    permute(str, 0, str.size());
}

/*
beg = 0
    i = 0
        s: [a]-b-c
        p: beg = 1
            i = 1
                s: a-[b]-c
                p: beg = 2  ---> a-b-c
                s: a-[b]-c
            i = 2
                s: a-[c]-[b]
                p: beg = 2  ---> a-c-b
                s: a-[b]-[c]
        s: [a]-b-c
    i = 1
        s: [b]-[a]-c
        p: beg = 1
            i = 1
                s: b-[a]-c
                p: beg = 2  ---> b-a-c
                s: b-[a]-c
            i = 2
                s: b-[c]-[a]
                p: beg = 2  ---> b-c-a
                s: [a]-[b]-[c]
        s: [a]-[b]-c
    i = 2
        s: [c]-b-[a]
        p: beg = 1
            i = 1
                s: c-[b]-a
                p: beg = 2  ---> c-b-a
                s: c-[b]-a
            i = 2
                s: c-[a]-[b]
                p: beg = 2  ---> c-a-b
                s: c-[b]-[c]
        s: [a]-b-[c]
*/