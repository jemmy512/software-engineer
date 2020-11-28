#include <cassert>
#include <vector>
#include <iostream>

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Comparator = std::less<T>>
void heapifyDown(Iter begin, Iter cur, Iter end, Comparator comp);

/* Comparator = std::less<T> find Kth largest element,
 * Comparator = std::great<T> find Kth smallest element */
template<typename Container,
    typename T = typename Container::value_type,
    typename Comparator = std::less<T>>
typename Container::value_type heapSort(Container& data, int kth, Comparator comp = Comparator()) {
    kth = std::min(kth, data.size());

    for (auto i = kth/2-1; i >=0; --i)
        heapifyDown(data.begin(), data.begin()+i, data.begin()+kth, comp);

    for (auto i = kth; i < data.size(); ++i) {
        if (comp(data[0], data[i])) {
            std::swap(data[i], data[0]);
            heapifyDown(data.begin(), data.begin(), data.begin()+kth, comp);
        }
    }

    return data[0];
}

// error: template parameter redefines default argument
// template<typename Iter,
//     typename T = typename std::iterator_traits<Iter>::value_type,
//     typename Comparator = std::less<T>>
template<typename Iter, typename T, typename Comparator>
void heapifyDown(Iter begin, Iter cur, Iter end, Comparator comp) {
    auto parent = cur;
    auto child = cur;
    for (std::advance(child, std::distance(begin, child) + 1);
        child < end;
        std::advance(child, std::distance(begin, child) + 1)
    ) {
        if (child + 1 < end && comp(*(child+1), *(child)))
            ++child;
        if (!comp(*child, *parent))
            break;
        std::swap(*parent, *child);
        parent = child;
    }
}

int main() {
    std::vector<int> data{3,2,5,8,4,7,6,9,0,1};

    std::cout << "The 5th smallest element: " << heapSort(data, 5, std::greater<int>()) << std::endl;

    std::cout << "The 2nd largest element: " << heapSort(data, 2, std::less<int>()) << std::endl;
}