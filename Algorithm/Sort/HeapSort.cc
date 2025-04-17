#include <iostream>
#include <iterator>
#include <vector>
#include <initializer_list>

/** Application:
 * 1. Priority Queue:
 *   1.1 Merge sorted small files
 *   1.2 High-performance timer
 * 2. Top K
 * 3. Median */

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Comparator = std::less<T>>
void heapifyDown(Iter begin, Iter cur, Iter end, Comparator comp) {
    Iter child = cur;
    Iter parent = cur;
    for (std::advance(child, std::distance(begin, child) + 1);// child = 2 * parent + 1
        child < end;
        std::advance(child, std::distance(begin, child) + 1))
    {
        if (child + 1 < end && comp(*(child+1), *child))    // comp(rightChild, leftChild)
            ++child;

        if (comp(*parent, *child))
            break;

        std::swap(*parent, *child);
        parent = child;
    }
}

// heapifyUp is designed for inserting a single element into an existing heap,
// not for building a heap from scratch.
template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Comparator = std::less<T>>
void heapifyUp(Iter begin, Iter end, Comparator comp) {    // [begin, end)
    Iter parent = begin;
    Iter child = end;
    for (parent = begin + std::distance(begin, child)/2-1; // parent = (child + 1 ) / 2 - 1
        parent >= begin;
        parent = begin + std::distance(begin, child)/2-1)
    {
        if (!comp(*--child, *parent))
            break;

        std::swap(*parent, *child);
        child = parent+1;
    }
}


template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Comparator = std::less<T>>
void heapSort(Iter begin, Iter end, Comparator comp = Comparator()) {
    // Converts the array into a max-heap.
    for (Iter iter = begin + std::distance(begin, end) / 2 - 1; iter >= begin; --iter) {
        heapifyDown(begin, iter, end, comp);
    }

    // Extract Elements and Build Sorted Array
    for (Iter iter = end - 1; iter > begin; --iter) {
        std::swap(*begin, *iter);
        heapifyDown(begin, begin, iter, comp);
    }
}

template<
    typename T,
    typename Comparator = std::less<T>,
    typename Container = std::vector<T>,
    typename OppositeComparator = typename std::conditional_t<
        std::is_same_v<Comparator, std::less<T>>,
        std::greater<T>,
        std::less<T>
    >
>
class Heap {
public:
    using container_type = Container;
    using value_compare = Comparator;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using iterator = typename Container::iterator;
    using const_reference = typename Container::const_reference;

    friend std::ostream& operator<<(std::ostream& os, const Heap& heap) {
        std::for_each(heap._Container.begin(), heap._Container.end(), [&os](const auto& data) {
           os << data << " ";
        });
        os << std::endl;

        return os;
    }

public:
    Heap() = default;

    Heap(std::initializer_list<T> list) : _Container(list.begin(), list.end()) {
        heapSort(_Container.begin(), _Container.end(), _Comparator);
    }

    Heap(const Heap& other) : _Container(other._Container) { }

    Heap(Heap&& other) : _Container(std::move(other._Container)) {
        other._Container.clear();
    }

    Heap& operator=(const Heap& other) {
        _Container = other._Container;

        return *this;
    }

    Heap& operator=(Heap&& other) {
        if (this != &other) {
            _Container = std::move(other._Container);
            other._Container.clear();
        }

        return *this;
    }

    void push(const T& value) {
        _Container.emplace_back(value);
        // heapifyUp(_Container.begin(), _Container.end(), _OppositeComparator);
        // heapifyDown(_Container.begin(), _Container.begin(), _Container.end(), _Comparator);
        heapSort(_Container.begin(), _Container.end(), _Comparator);
    }

    value_type pop_back() {
        T result = _Container.back();

        _Container.pop_back();

        return result;
    }

    value_type pop_front() {
        T result = _Container.front();

        _Container = {_Container.begin()+1, _Container.end()};

        return result;
    }

    const_reference top() {
        return _Container.front();
    }

    bool empty() {
        return _Container.empty();
    }

private:
    Container _Container;
    Comparator _Comparator{};
    OppositeComparator _OppositeComparator{};

};

void TestHeapSort() {
    std::vector<int> vec{3, 2, 5, 8, 4, 7, 6, 12, 1, 0};
    // heapSort(vec.begin(), vec.end());
    heapSort(vec.begin(), vec.end(), std::greater<int>());
    std::move(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    vec.emplace_back(9);
    heapifyUp(vec.begin(), vec.end(), std::less<int>());

    std::move(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void TestHeap() {
    std::vector<int> vec{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    // Heap<int> heap;
    Heap<int> heap;
    for (const auto& v : vec) {
        heap.push(v);
        std::cout << heap << std::endl;
    }

    for (const auto& v : vec) {
        auto val = heap.pop_front();
        std::cout << val << ": " << heap << std::endl;
    }
}


int main(void) {
    TestHeapSort();

    // TestHeap();

    return 0;
}