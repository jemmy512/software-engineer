#include<iostream>
#include<vector>
#include<iterator>
#include <chrono>
#include <random>

using namespace std;

template<typename Size = int>
Size getRandom(Size min, Size max) {
    std::random_device dev;
    std::default_random_engine engine(dev());
    std::uniform_int_distribution<Size> distribution(min, max);

    return distribution(engine);
}


template<typename T>
void quickSort(T& data, int beg, int end) { // [begin, end}
    if (data.size() == 0 || beg + 1 >= end) {
        return;
    }

    int open = beg;
    int close = end-1;
    int pivot = data[getRandom(open, close)];
    while (open <= close) {
        while (data[open] < pivot)
            ++open;
        while (data[close] > pivot)
            --close;
        if (open <= close)
            std::swap(data[open++], data[close--]);
    }

    quickSort(data, beg, open);
    quickSort(data, open+1, end);
}

int main(void) {
    vector<int> data = {3, 2, 5, 8, 4, 7, 6, 9};
    quickSort(data, 0, data.size());
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
    return 0;
}

/*
1', 12, 5, 26, 7, 14, 3, 7, 2^

1, 12', 5, 26, 7, 14, 3, 7, 2^

1, 2, 5, 26', 7, 14, 3, 7^, 12

1, 2, 5, 7, 7', 14, 3^, 26, 12

1, 2, 5, 7, 3, 14'^, 7, 26, 12 --> 1, 2, 5, 7, 3^, 14', 7, 26, 12

1, 2, 5, 7, 3, 3'^, 7, 26, 12 --> 1, 2, 5, 7, 3, 3^, 7', 26, 12 */