#include <iostream>
#include <vector>

using namespace std;

template<typename T>
int partition(T& data, int beg, int end) {
    int i = beg + 1;
    int pivot = data[beg];

    for (int j = i; j < end; ++j) {
        if (data[j] < pivot) {
            swap(data[i++], data[j]);
        }
    }

    swap(data[beg], data[i-1]);

    return i-1;
}

template<typename T>
void quickSort(T& data, int beg, int end) {
    if (beg < end) {
        auto pivot = partition(data, beg, end);
        quickSort(data, beg, pivot);
        quickSort(data, pivot+1, end);
    }
}

int main(void) {
    vector data{3, 3, 2, 5, 3, 3, 8, 4, 7, 6, 9, 3, 3};
    quickSort(data, 0, data.size());
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
}

/*
1', 12, 5, 26, 7, 14, 3, 7, 2^

1, 12', 5, 26, 7, 14, 3, 7, 2^

1, 2, 5, 26', 7, 14, 3, 7^, 12

1, 2, 5, 7, 7', 14, 3^, 26, 12

1, 2, 5, 7, 3, 14'^, 7, 26, 12 --> 1, 2, 5, 7, 3^, 14', 7, 26, 12

1, 2, 5, 7, 3, 3'^, 7, 26, 12 --> 1, 2, 5, 7, 3, 3^, 7', 26, 12 */