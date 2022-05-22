#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void insertSort(T& data) {
    for (auto i = 1; i < data.size(); ++i) {
        for (int j = i; j > 0; --j) {
            if (data[j-1] > data[j]) {
                std::swap(data[j-1], data[j]);
            } else {
                break;
            }
        }
    }
}

int main(void) {
    vector vec{3, 2, 5, 8, 4, 7, 6, 9};
    insertSort(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}