#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void quickSort(T& data, int beg, int end) {
    if (data.size() == 0 || beg >= end) {
        return;
    }

    int lbeg = beg;
    int lend = end-1;
    int pivot = data[beg];
    while (lbeg < lend) {
        while (lbeg < lend && data[lend] > pivot) --lend;
        if (lbeg < lend) data[lbeg++] = data[lend];
        while (lbeg < lend && data[lbeg] < pivot) ++lbeg;
        if (lbeg < lend) data[lend--] = data[lbeg];
    }

    data[lbeg] = pivot;
    quickSort(data, beg, lbeg-1);
    quickSort(data, lend+1, end);
}

int main(void) {
    vector<int> data = {3, 2, 5, 8, 4, 7, 6, 9};
    quickSort(data, 0, data.size());
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
    return 0;
}
