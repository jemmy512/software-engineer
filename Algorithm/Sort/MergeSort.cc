#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void mergeArray(vector<T> &data, int beg, int mid, int end, vector<T> &tmpData) {
    int lbeg = beg, rbeg = mid;
    int i = beg;
    
    while (lbeg != mid && rbeg != end) {
        tmpData[i++] = data[lbeg] < data[rbeg] ? data[lbeg++] : data[rbeg++];
    }
    
    while (lbeg != mid)
        tmpData[i++] = data[lbeg++];
    while (rbeg != end)
        tmpData[i++] = data[rbeg++];
    for (i = beg; i < end; ++i)
        data[i] = tmpData[i];
}

template<typename T>
void mergeSort(vector<T> &data, int beg, int end, vector<T> &tmpData) {
    int mid = (beg + end) / 2;
    if (mid != beg) {
        mergeSort(data, beg, mid, tmpData);
        mergeSort(data, mid, end, tmpData);
        mergeArray(data, beg, mid, end, tmpData);
    }
}

int main(void) {
    // vector<int> data = {3, 2, 5, 8, 4, 7, 6, 9};
    // vector<float> tmpData(data.size());   
    vector<float> data = {3.0, 2.3, 5.5, 8.3, 4.4, 7.6, 6.6, 9.8};
    vector<float> tmpData(data.size());
    mergeSort(data, 0, data.size() - 1, tmpData);
    
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
    return 0;
}