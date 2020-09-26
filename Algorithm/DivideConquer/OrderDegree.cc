#include <iostream>
#include <vector>
#include <iterator>

template<
    typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
void merge(Iter begin, Iter mid, Iter end, Compare comp = Compare()) {
    std::vector<T> vec(std::distance(begin, end));

    auto lb = begin, rb = mid;
    while (lb < mid && rb < end) {
        if (!comp(*rb, *lb)) {

        } else {

        }
    }

    while (lb < mid) {

    }

    while (rb < end) {

    }



}

template<typename Iter>
void mergeCounting(Iter begin, Iter end) {
    auto mid = begin + std::distance(begin, end) / 2;
    if (begin < mid) {
        mergeCounting(begin, mid);
        mergeCounting(mid, end);
        merge(begin, mid, end);
    }

}

template<typename Iter>
int count(Iter begin, Iter end) {

}
