/* Author: Jemmy
 * Time: 2020-03-21 */

#include <iostream>
#include <vector>

enum class SearchPolicy {
    Undefined,           // default binary search
    First,              // find the first element
    Last,               // find the last element
    FirstNotLessThan,   // find the first element not less than
    LastNotGreatThan    // find the last element not great than
};

// Best performance when Iter is random iterator

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
Iter binarySearch(Iter begin, Iter end, const T& val, Compare comp = Compare())
{
    auto result = end;

    while (std::distance(begin, end) > 0) {
        auto mid = begin + std::distance(begin, end) / 2;
        if (comp(*mid, val)) {
            begin = mid + 1;
        } else if (comp(val, *mid)) {
            end = mid;
        } else {
            result = mid;
            break;
        }
    }

    return result;
}

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>,
    typename Compare = std::less<T>>
Iter binarySearchFirst(Iter begin, Iter end, const T& val, Compare comp = Compare()) {
    auto result = end;

    while (std::distance(begin, end) > 0) {
        auto mid = begin + std::distance(begin, end) / 2;
        if (comp(*mid, val)) {
            begin = mid + 1;
        } else if (comp(val, *mid)) {
            end = mid;
        } else {
            if (mid == begin || comp(*(mid-1), *mid)) {
                result = mid;
                break;
            } else {
                end = mid;
            }
        }
    }

    return result;
}

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
Iter binarySearchLast(Iter begin, Iter end, const T& val, Compare comp = Compare()) {
    auto result = end;

    while (std::distance(begin, end) > 0) {
        auto mid = begin + std::distance(begin, end) / 2;
        if (comp(*mid, val)) {
            begin = mid + 1;
        } else if (comp(val, *mid)) {
            end = mid;
        } else {
            if (std::distance(mid, end) == 1 || comp(*mid, *(mid+1))) {
                result = mid;
                break;
            } else {
                begin = mid + 1;
            }
        }
    }

    return result;
}

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
Iter binarySearchFirstNotLess(Iter begin, Iter end, const T& val, Compare comp = Compare()) {
    auto result = end;

    while (std::distance(begin, end) > 0) {
        auto mid = begin + std::distance(begin, end) / 2;
        if (!comp(*mid, val)) { // val <= *mid
            if (mid == begin || comp(*(mid-1), val)) {
                result = mid;
                break;
            } else {
                end = mid;
            }
        } else {
            begin = mid + 1;
        }
    }

    return result;
}

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
Iter binarySearchLastNotGreat(Iter begin, Iter end, const T& val, Compare comp = Compare()) {
    auto result = end;

    while (std::distance(begin, end) > 0) {
        auto mid = begin + std::distance(begin, end) / 2;
        if (!comp(val, *mid)) { // *mid <= val
            if (std::distance(mid, end) == 1 || comp(val, *(mid+1))) {
                result = mid;
                break;
            } else {
                begin = mid + 1;
            }
        } else {
            end = mid;
        }
    }

    return result;
}

template<typename Iter,
    typename T = typename std::iterator_traits<Iter>::value_type,
    typename Compare = std::less<T>>
Iter binarySearchApi(Iter begin, Iter end, const T& val, SearchPolicy policy = SearchPolicy::Undefined, Compare comp = Compare())
{
    /* switch run faster than if else */
    switch (policy) {
        case SearchPolicy::Undefined:
            return binarySearch(begin, end, val, comp);
        case SearchPolicy::First:
            return binarySearchFirst(begin, end, val, comp);
        case SearchPolicy::Last:
            return binarySearchLast(begin, end, val, comp);
        case SearchPolicy::FirstNotLessThan:
            return binarySearchFirstNotLess(begin, end, val, comp);
        case SearchPolicy::LastNotGreatThan:
            return binarySearchLastNotGreat(begin, end, val, comp);
        default:
            return end;
    }
}

template <typename VecT, typename T = typename VecT::value_type>
void TestBinarySearch(const VecT& data, T target,
    SearchPolicy policy = SearchPolicy::Undefined)
{
    auto it = binarySearchApi(data.begin(), data.end(), target, policy);
    std::cout << "search[" << target << "], distance: " << std::distance(data.begin(), it) << std::endl;
}


int main() {
    std::vector<int> data{0, 0, 1, 2, 3, 4, 4, 5, 5, 5, 5, 5, 6, 8};

    std::cout << "------------ Undefined ------------" << std::endl;
    TestBinarySearch(data, -1);                                     // 13
    TestBinarySearch(data, 0);                                      // 0, 1
    TestBinarySearch(data, 5);                                      // 7, 8, 9, 10, 11
    TestBinarySearch(data, 8);                                      // 13
    TestBinarySearch(data, 10);                                     // 14

    std::cout << "\n\n------------ First ------------" << std::endl;
    TestBinarySearch(data, -1, SearchPolicy::First);                // 14
    TestBinarySearch(data, 0, SearchPolicy::First);                 // 0
    TestBinarySearch(data, 5, SearchPolicy::First);                 // 7
    TestBinarySearch(data, 7, SearchPolicy::First);                 // 14
    TestBinarySearch(data, 8, SearchPolicy::First);                 // 13
    TestBinarySearch(data, 10, SearchPolicy::First);                // 14

    std::cout << "\n\n------------ Last ------------" << std::endl;
    TestBinarySearch(data, -1, SearchPolicy::Last);                 // 14
    TestBinarySearch(data, 0, SearchPolicy::Last);                  // 1
    TestBinarySearch(data, 5, SearchPolicy::Last);                  // 11
    TestBinarySearch(data, 7, SearchPolicy::Last);                  // 14
    TestBinarySearch(data, 8, SearchPolicy::Last);                  // 13
    TestBinarySearch(data, 10, SearchPolicy::Last);                 // 14

    std::cout << "\n\n------------ FirstNotLessThan ------------" << std::endl;
    TestBinarySearch(data, -1, SearchPolicy::FirstNotLessThan);     // 0
    TestBinarySearch(data, 0, SearchPolicy::FirstNotLessThan);      // 0
    TestBinarySearch(data, 5, SearchPolicy::FirstNotLessThan);      // 7
    TestBinarySearch(data, 7, SearchPolicy::FirstNotLessThan);      // 13
    TestBinarySearch(data, 8, SearchPolicy::FirstNotLessThan);      // 13
    TestBinarySearch(data, 10, SearchPolicy::FirstNotLessThan);     // 14

    std::cout << "\n\n------------ LastNotGreatThan ------------" << std::endl;
    TestBinarySearch(data, -1, SearchPolicy::LastNotGreatThan);     // 14
    TestBinarySearch(data, 0, SearchPolicy::LastNotGreatThan);      // 1
    TestBinarySearch(data, 5, SearchPolicy::LastNotGreatThan);      // 11
    TestBinarySearch(data, 7, SearchPolicy::LastNotGreatThan);      // 12
    TestBinarySearch(data, 8, SearchPolicy::LastNotGreatThan);      // 13
    TestBinarySearch(data, 10, SearchPolicy::LastNotGreatThan);     // 13

    return 0;
}