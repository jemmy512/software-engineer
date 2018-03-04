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

template<typename T>
void bubble_sort(array<T, 8> &arr, int n) {
    bool flag = true;                         // optimization
    int temp;
    for (int i = 0; i < n - 1 && flag; ++i) { // control the loop number of bubbles
        flag = false;
        for (int j = 0; j < n - 1 - i; ++j) { // control each bubble
            if (arr[j] > arr[j + 1]) {
                flag = true;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    array<int, 8> arr = {3, 2, 5, 8, 4, 7, 6, 9};
    bubble_sort(arr, 8);
    copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
}
