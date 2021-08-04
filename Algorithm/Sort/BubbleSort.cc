/*
*   This is an optimized bubble sort algorithm that the algorithm complete
*   when there were no elements exchanged in one loop.
*
*   author: Jemmy Wong
*   date: 2018-02-25
*/
#include<iostream>
#include<algorithm>
#include<iterator>
#include<array>

using namespace std;

template<typename T, size_t N>
void bubbleSort(std::array<T, N>& data) {
    auto isUpdated = true;

    for (auto i = 0; i < data.size() - 1 && isUpdated; ++i) {
        isUpdated = false;
        for (auto j = 0; j < data.size() - 1 - i; ++j) {
            if (data[j] > data[j+1]) {
                isUpdated = true;
                std::swap(data[j], data[j+1]);
            }
        }
    }
}

int main(void) {
    array<int, 8> arr = {3, 2, 5, 8, 4, 7, 6, 9};
    bubbleSort<int, 8>(arr);
    copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
}
