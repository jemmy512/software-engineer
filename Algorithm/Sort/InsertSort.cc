#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

void insertSort(vector<int> &vec) {
    for (int i = 1; i < vec.size(); ++i) {
        for (int j = i; j > 0; --j) {
            if (vec[j] < vec[j - 1])
                swap(vec[j], vec[j - 1]);
        }
    }
}

int main(void) {
    vector<int> vec = {3, 2, 5, 8, 4, 7, 6, 9};
    insertSort(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}