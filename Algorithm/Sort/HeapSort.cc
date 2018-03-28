#include<iostream>
#include<iterator>
#include<vector>

using namespace std;

void heapAdjust(vector<int> &vec, int b, int e) {
    for (int i = 2 * b + 1; i < e; i = i * 2 + 1) {
        if (i + 1 < e && vec[i] < vec[i + 1])
            ++i;
        if (vec[b] >= vec[i])
            break;
        swap(vec[b], vec[i]);
        b = i;
    }
}

void heapSort(vector<int> &vec) {
    int len = vec.size();
    for (int i = len / 2 - 1; i >= 0; --i) 
        heapAdjust(vec, i, len);
    for (int i = len - 1; i > 0; --i) {
        swap(vec[0], vec[i]);
        heapAdjust(vec, 0, i);
    }
}

int main(void) {
    vector<int> vec = {3, 2, 5, 8, 4, 7, 6, 9};
    heapSort(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    
    return 0;
}