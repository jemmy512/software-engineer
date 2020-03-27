#include<iostream>
#include<iterator>
#include<vector>

/**
 * Top to bottom heapify */
template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
void heapify(Iter begin, Iter cur, Iter end, Compare comp = Compare()) {
    for (Iter iter = cur + std::distance(begin, cur) + 1;
        iter < end;
        iter = iter + std::distance(begin, iter) + 1)
    {
        if (iter + 1 < end && comp(*iter, *(iter+1)))
            ++iter;             // max(leftChild, rightChild)

        if (!comp(*cur, *iter)) // max(cur, child)
            break;

        std::swap(*cur, *iter);
        cur = iter;
    }
}


template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
void heapSort(Iter begin, Iter end, Compare comp = Compare()) {
    for (Iter iter = begin + std::distance(begin, end) / 2 - 1; iter >= begin; --iter)
        heapify(begin, iter, end, comp);

    for (Iter iter = end - 1; iter > begin; --iter) {
        std::swap(*begin, *iter);
        heapify(begin, begin, iter, comp);
    }
}

int main(void) {
    std::vector<int> vec{3, 2, 5, 8, 4, 7, 6, 9, 1};

    // heapSort(vec.begin(), vec.end());
    heapSort(vec.begin(), vec.end(), std::greater<int>());

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}