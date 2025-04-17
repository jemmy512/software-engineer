#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void insertSort(T& vec) {
    for (auto i = 1; i < vec.size(); ++i) {
        auto key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j+1] = vec[j];
            --j;
        }
        vec[j+1] = key;
    }
}

int main(void) {
    vector vec{3, 2, 5, 8, 4, 7, 6, 9};
    insertSort(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}