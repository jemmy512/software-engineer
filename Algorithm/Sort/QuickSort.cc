#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void quickSort(vector<T> &data, int beg, int end) {
    if (beg >= end)
        return;

    int b, e, index;
    b = beg;
    e = end;
    index = data[beg];
    while (b < e)  {
        while (b < e && data[e] > index) --e;
        if (b < e) data[b++] = data[e];
        while (b < e && data[b] < index) ++b;
        if (b < e) data[e--] = data[b];
    }

    data[b] = index;
    quickSort(data, beg, b - 1);
    quickSort(data, b + 1, end);
}

int main(void) {
    vector<int> data = {3, 2, 5, 8, 4, 7, 6, 9};
    quickSort(data, 0, 7);
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
    return 0;
}
