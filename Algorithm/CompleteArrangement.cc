/*
*   This algorithm implements the 1-N numbers complete arrangement
*   author: Jemmy Wong
*   date: 2018-02-25
*/
#include<iostream>
#include<array>
#include<iterator>

using namespace std;

#define N 3

array<int, 3> arr;

void arrange(int n) {
    if (n == N -1) {
        copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        return;
    }
    for (int i = n; i < N; ++i) {
        swap(arr[n], arr[i]);
        arrange(n + 1);
        swap(arr[n], arr[i]);
    }
  
}

int main(int argc ,char* argv[]) {
    for (int i = 0; i < 3; ++i)
        arr[i] = i + 1;
    arrange(0);
    
    return 0;
}
