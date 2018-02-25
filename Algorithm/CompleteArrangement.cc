/*
*   This algorithm implements the 1-N numbers complete arrangement
*   author: Jemmy Wong
*   date: 2018-02-25
*/
#include<iostream>
#include<algorithm>
#include<array>

#define N 3

using namespace std;

array<int, N> arr;
int total = 0;

void init() {
    for (int i = 0; i < N; ++i)
        arr[i] = i + 1;
}

void print() {
    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void arrange(int n) {
    if (n == N - 1) {
        print();
        total++;
        return;
    }
    for (int i = n; i < N; ++i) {
        swap(arr[n], arr[i]);
        arrange(n + 1);
        swap(arr[n], arr[i]);
    }
}

int main(void ) {
    init();
    arrange(0);
    cout << endl << "total: " << total << endl;

    return 0;
}

