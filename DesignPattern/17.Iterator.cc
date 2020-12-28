#include <iostream>
#include <iterator>
#include <cstddef> // std::ptrdiff_t

template<size_t Size>
class Integers {
public:
    struct iterator {
        using iterator_catogory = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int*;
        using reference = int&;

        iterator(pointer ptr) : _Ptr(ptr) {}

        reference operator*() { return *_Ptr; }
        pointer operator->() { return _Ptr; }
        iterator operator++() { ++_Ptr; return *this; }
        iterator operator++(int) { auto tmp = *this; ++_Ptr; return tmp; }
        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs._Ptr == rhs._Ptr; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return lhs._Ptr != rhs._Ptr; }

    private:
        pointer _Ptr;
    };

    struct const_iterator {
        using iterator_catogory = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using const_pointer = const int*;
        using const_reference = const int&;

        const_iterator(const_pointer ptr) : _Ptr(ptr) {}

        const_reference operator*() { return *_Ptr; }
        const_pointer operator->() { return _Ptr; }
        const_iterator operator++() { ++_Ptr; return *this; }
        const_iterator operator++(int) { auto tmp = *this; ++_Ptr; return tmp; }
        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) { return lhs._Ptr == rhs._Ptr; }
        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) { return lhs._Ptr != rhs._Ptr; }

    private:
        const_pointer _Ptr;
    };

    Integers(std::initializer_list<int> list) {
        for (int i = 0; i < list.size(); ++i) {
            _Data[i] = *(list.begin()+i);
        }
    }

    iterator begin() { return iterator(&_Data[0]); }
    iterator end() { return iterator(&_Data[Size]); }

    const_iterator cbegin() { return const_iterator(&_Data[0]); }
    const_iterator cend() { return const_iterator(&_Data[Size]); }

private:
    int _Data[Size];
};

int main() {
    Integers<5> ints = {1, 2, 3, 4, 5};
    std::copy(ints.begin(), ints.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::copy(ints.cbegin(), ints.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}