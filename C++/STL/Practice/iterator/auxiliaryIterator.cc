#include<iostream>
#include<iterator>
#include<algorithm>
#include<array>

using namespace std;

int main(void) {
    
    
    array<int, 10> arr;
    for (int i = 0; i < 10; ++i) {
        arr[i] = i;
    }
    
    array<int, 10>::iterator iter;
    iter = find(arr.begin(), arr.end(), 5);
    cout << "distance of 5 in arr: " << distance(arr.begin(), iter) << endl;
    
    cout << "previous element of 5 using prev(): " << *prev(iter) << endl;
    cout << "next element of 5 using next(): " << *next(iter) << endl;
    cout << "old value of arr[0]: " << arr[0] << ", arr[4]: " << arr[4];
    iter_swap(arr.begin(), iter);
    cout << " -|- " << "old value of arr[0]: " << arr[0] << ", arr[4]: " << arr[4] << endl;
}