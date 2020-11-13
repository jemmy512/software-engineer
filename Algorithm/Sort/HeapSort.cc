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
    typename Compare = std::less<T>>
void heapifyDown(Iter begin, Iter cur, Iter end, Compare comp = Compare()) {
    Iter child = cur;
    Iter parent = cur;
    for (std::advance(child, std::distance(begin, child) + 1);// child = 2*cur + 1
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

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
void heapifyUp(Iter begin, Iter end, Compare comp = Compare()) {    // [begin, end)
    Iter parent = begin;
    Iter child = end;
    for (std::advance(parent, std::distance(begin, child) / 2 - 1);   // parent = (cur+1)/2 - 1
        parent >= begin;
        std::advance(parent, std::distance(begin, child) / 2 - 1))
    {
        if (!comp(*--child, *parent))
            break;

        std::swap(*parent, *child);
        child = parent+1;
        parent = begin;
    }
}


template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
void heapSort(Iter begin, Iter end, Compare comp = Compare()) {
    for (Iter iter = begin + std::distance(begin, end) / 2 - 1; iter >= begin; --iter)
        heapifyDown(begin, iter, end, comp);

    for (Iter iter = end - 1; iter > begin; --iter) {
        std::swap(*begin, *iter);
        heapifyDown(begin, begin, iter, comp);
    }
}

template<
    typename T,
    typename Compare = std::less<T>,
    typename Container = std::vector<T>>
class Heap {
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using iterator = typename Container::iterator;
    using const_reference = typename Container::const_reference;

    friend std::ostream& operator<<(std::ostream& os, const Heap& heap) {
        for (const auto& v : heap._Container)
            os << v << " ";
        os << std::endl;

        return os;
    }

public:
    Heap() = default;

    Heap(std::initializer_list<T> list) {
        for (const auto& v : list) {
            push(v);
        }
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

    void update(const T& value) {
        auto iter = std::find_if(_Container.begin(), _Container.end(), [&value](const auto& val) {
            return val.get() == value.get();
        });

        if (iter != _Container.end()) {
            heapifyUp(_Container.begin(), ++iter, _Comparator);
        }
    }

    void push(const T& value) {
        _Container.emplace_back(value);
        heapifyUp(_Container.begin(), _Container.end(), _Comparator);
    }

    value_type pop() {
        T result = _Container.front();

        std::swap(_Container.front(), _Container.back());
        _Container.pop_back();
        heapifyDown(_Container.begin(), _Container.begin(), _Container.end(), _Comparator);

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
    Compare _Comparator{};

};

void TestHeapSort() {
    std::vector<int> vec{3, 2, 5, 8, 4, 7, 6, 9, 1};

    // heapSort(vec.begin(), vec.end());
    heapSort(vec.begin(), vec.end(), std::greater<int>());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    vec.emplace_back(12);
    heapifyUp(vec.begin(), vec.end(), std::greater<int>());

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void TestHeap() {
    std::vector<int> vec{3, 2, 5, 8, 4, 7, 6, 9, 1};
    // Heap<int> heap;
    Heap<int, std::greater<int>> heap;
    for (const auto& v : vec) {
        heap.push(v);
        std::cout << heap << std::endl;
    }

    for (const auto& v : vec) {
        auto val = heap.pop();
        std::cout << val << ": " << heap << std::endl;
    }
}


// int main(void) {
//     // TestHeapSort();

//     TestHeap();

//     return 0;
// }