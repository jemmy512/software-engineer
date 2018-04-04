#include<iostream>
#include<string>

using namespace std;

int *getNext(const string &ps) {
    int len = ps.size();
    int *next = new int[len];
    int i = 0;
    int k = -1;
    next[0] = -1;
    while(i < len) {
        if (k == -1 || ps[i] == ps[k]) {
            ++i;
            ++k;
            if (ps[i] == ps[k])
                next[i] = next[k];
            else
                next[i] = k;
        } else 
            k = next[k];
    }
    return next;
        
}

int kmp(const string &ts, const string &ps) {
    int len_t = ts.size();
    int len_p = ps.size();
    int *next = getNext(ps); 
    int i, j;
    i = j = 0;
    while (i < len_t && j < len_p) {
        if (j == -1 || ts[i] == ps[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    
    delete next;
    
    if (j == len_p)
        return i - j;
    return -1;
}

int main(void) {
    string ts = "abcdabcvfd";
    string ps = "dab";
    int ret = kmp(ts, ps);
    cout << ret << endl;
    return 0;
}