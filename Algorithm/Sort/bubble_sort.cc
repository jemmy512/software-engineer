#include<iostream>
#include<algorithm>
#include<iterator>
#include<array>

using namespace std;

void bubble_sort(array<int, 8> arr, int n) {
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

    copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
}

int main(void) {
    array<int, 8> arr = {3, 2, 5, 8, 4, 7, 6, 9};
    bubble_sort(arr, 8);
}
