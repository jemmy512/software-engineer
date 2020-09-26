#include<iostream>
#include<vector>

using namespace std;

template<typename T>
void merge(T& data, int beg, int mid, int end) {
    T tmpData(data.size());
    int lbeg = beg, rbeg = mid, i = beg;

    while (lbeg < mid && rbeg < end)
        tmpData[i++] = data[lbeg] < data[rbeg] ? data[lbeg++] : data[rbeg++];

    while (lbeg < mid)
        tmpData[i++] = data[lbeg++];

    while (rbeg < end)
        tmpData[i++] = data[rbeg++];

    for (i = beg; i < end; ++i)
        data[i] = tmpData[i];
}

template<typename T>
void mergeSort(T& data, int beg, int end) {
    int mid = beg + (end - beg) / 2; // (beg + end) may overflow
    if (beg != mid) {
        mergeSort(data, beg, mid);
        mergeSort(data, mid, end);
        merge(data, beg, mid, end);
    }
}

int main(void) {
    vector<float> data = {3.0, 2.3, 5.5, 8.3, 4.4, 7.6, 6.6, 9.8};
    mergeSort(data, 0, data.size());
    copy(data.begin(), data.end(), ostream_iterator<float>(cout, " "));

    return 0;
}