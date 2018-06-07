/*
*   This algorithm implements the 1-N numbers complete arrangement
*   author: Jemmy Wong
*   date: 2018-02-25
*/
#include<iostream>
#include<array>
#include<iterator>

using namespace std;

bool isSwap(string str, int beg, int end) {
    for (; beg < end; ++beg) {
        if (str[beg] == str[end])
            return false;
    }
    
    return true;
}

void arrange_recursive(string str, int k) {
    int len = str.size();
    if (k == len) {
        cout << str << endl;
    } else {
        for (int i = k; i < len; ++i) {
            if (isSwap(str, k, i)) {
                swap(str[k], str[i]);
                arrange(str, k + 1);
                swap(str[k], str[i]);                
            }
        }
    }
}

int main(int argc ,char* argv[]) {
    string str = "122";
    arrange(str, 0);
    
    return 0;
}
