#include<iostream>
#include<vector>

using namespace std;

template<typename T>
void merge(T& data, int beg, int mid, int end) {
    T vec(data.size());
    int lbeg = beg, rbeg = mid, i = beg;

    while (lbeg < mid && rbeg < end)
        vec[i++] = data[lbeg] < data[rbeg] ? data[lbeg++] : data[rbeg++];

    while (lbeg < mid)
        vec[i++] = data[lbeg++];

    while (rbeg < end)
        vec[i++] = data[rbeg++];

    for (i = beg; i < end; ++i)
        data[i] = vec[i];
}

template<typename T>
void mergeSort(T& data, int beg, int end) {
    // if (beg < end) [0, 1) can cause dead loop

    int mid = beg + (end - beg) / 2;
    if (beg < mid) {
        mergeSort(data, beg, mid);
        mergeSort(data, mid, end);
        merge(data, beg, mid, end);
    }
}

int main(void) {
    vector data{3, 5, 2, 3, 8, 4, 7, 5, 3, 6, 7, 2, 5, 7};
    mergeSort(data, 0, data.size());
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
}