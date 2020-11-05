#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename T>
void insertSort(T& data) {
    for (int i = 1; i < data.size(); ++i) {
        int tmp = data[i];
        int j = i;
        while (j > 0 && data[j-1] > tmp) {
            data[j] = data[j-1];
            --j;
        }

        data[j] = tmp;
    }
}

int main(void) {
    vector<int> vec = {3, 2, 5, 8, 4, 7, 6, 9};
    insertSort(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}