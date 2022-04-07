#include <iostream>
#include <vector>
#include <random>

using namespace std;

template<typename Size = int>
Size getRandom(Size min, Size max) {
    std::random_device dev;
    std::default_random_engine engine(dev());
    std::uniform_int_distribution<Size> distribute(min, max);

    return distribute(engine);
}

// left <= pivot < right
template<typename T>
int partition(T& data, int beg, int end) {// [beg, end}
    --end;
    auto pivot = data[getRandom(beg, end)];

    while (beg <= end) {
        while (beg < end && data[beg] <= pivot)
            ++beg;
        while (beg < end && pivot < data[end])
            --end;

        if (beg <= end)
            swap(data[beg++], data[end--]);
    }

    return beg;
}

template<typename T>
void quickSort(T& data, int beg, int end) {
    if (beg + 1 < end) {
        auto pivot = partition(data, beg, end);
        /* dead loop if pivot not -1 +1 when beg = 0 end = 7 pivot = 3
        0 1 2 3 4 5 6 7 8 9 10 11 12
        3 3 2 3 3 3 3 4 7 6 5  9  8 */
        quickSort(data, beg, pivot-1);
        quickSort(data, pivot+1, end);
    }
}

template<typename T>
void quickSelectK(T& points, int beg, int end, int k) { // [beg, end}
    if (beg + 1 < end) {
        while (beg < end) {
            auto pivot = partition(points, beg, end);
            if (pivot < k) {
                beg = pivot + 1;
            } else if (pivot > k) {
                end = pivot - 1;
            } else {
                break;
            }
        }
    }

    std::cout << k << " [" << points[k] << "]" << std::endl;
}

int main(void) {
    vector data{3, 3, 2, 5, 3, 3, 8, 4, 7, 6, 9, 3, 3};
    quickSort(data, 0, data.size());
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
    std::cout << std::endl;

    quickSelectK(data, 0, data.size(), 1);
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
    std::cout << std::endl;

    quickSelectK(data, 0, data.size(), 10);
    copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
    std::cout << std::endl;
}

/* left <= [pivto = 5] < right
7' 5 2^ -> 2 5'^ 7 -> 2^ 5 7'
7' 5^ -> 5' 7^ */

/* left <= pivot < right
This solution doesn't chagne the first data, which will cause dead loop

beg = 0 end = 7 pivot = 3
0 1 2 3 4 5 6 7 8 9 10 11 12
3 3 2 3 3 3 3 4 7 6 5  9  8 */
template<typename T>
int partition_(T& data, int beg, int end) {
    int i = beg + 1;
    int pivot = data[beg];

    for (int j = i; j < end; ++j) {
        if (data[j] <= pivot) {
            swap(data[i++], data[j]);
        }
    }

    return i;
}