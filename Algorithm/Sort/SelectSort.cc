#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void selectSort(vector<T> &data) {
    
    int n = data.size();
    int min;
    for (int i = 0; i < n; ++i) {
        min = i;
        for (int j = i + 1; j < n; ++j) {
            if (data[j] < data[min])
                min = j;    
        }
        if (min == i)
            continue;
        data[i] += data[min];
        data[min] = data[i] - data[min];
        data[i] = data[i] - data[min];
    }
}

int main(void) {
    vector<int> data = {3, 2, 5, 8, 4, 7, 6, 9};
    selectSort(data);
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
}