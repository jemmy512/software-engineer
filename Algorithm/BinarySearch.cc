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
Iter binarySearch(Iter begin, Iter end, T val,
    SearchPolicy policy = SearchPolicy::Undefined,
    Compare comp = Compare())
{
    Iter result = end;

    while (std::distance(begin, end) > 0) {
        auto mid = begin + std::distance(begin, end) / 2;

        if (policy == SearchPolicy::FirstNotLessThan) {
            if (!comp(*mid, val)) { // val <= *mid
                if (mid == begin || comp(*(mid-1), *mid)) {
                    result = mid;
                    break;
                } else {
                    end = mid;
                }
            } else {
                begin = mid + 1;
            }
        } else if (policy == SearchPolicy::LastNotGreatThan) {
            if (!comp(val, *mid)) { // val >= *mid
                if (std::distance(mid, end) == 1 || comp(val, *(mid+1))) {
                    result = mid;
                    break;
                } else {
                    begin = mid + 1;
                }
            } else {
                end = mid;
            }
        } else {
            if (comp(val, *mid)) {
                end = mid;
            } else if (comp(*mid, val)) {
                begin = mid + 1;
            } else {
                if (policy == SearchPolicy::First) {
                    if (mid == begin || comp(*(mid-1), *mid)) {
                        result = mid;
                        break;
                    } else {
                        end = mid;
                    }
                } else if (policy == SearchPolicy::Last) {
                    if (std::distance(mid, end) == 1 || comp(*mid, *(mid+1))) {
                        result = mid;
                        break;
                    } else {
                        begin = mid + 1;
                    }
                } else {
                    result = mid;
                    break;
                }
            }
        }
    }

    return result;
}

template <typename VecT, typename T = typename VecT::value_type>
void TestBinarySearch(const VecT& test,
    T target,
    SearchPolicy policy = SearchPolicy::Undefined)
{
    auto it = binarySearch(test.begin(), test.end(), target, policy);
    std::cout << std::distance(test.begin(), it) << std::endl;
}


int main() {
    std::vector<int> test{0, 0, 1, 2, 3, 4, 4, 5, 5, 5, 5, 5, 6, 8};

    TestBinarySearch(test, 8);                                      // 13
    TestBinarySearch(test, -1);                                     // 14
    TestBinarySearch(test, 0);                                      // 0, 1
    TestBinarySearch(test, 0, SearchPolicy::First);                 // 0
    TestBinarySearch(test, 0, SearchPolicy::Last);                  // 1
    TestBinarySearch(test, 4);                                      // 5, 6
    TestBinarySearch(test, 4, SearchPolicy::First);                 // 5
    TestBinarySearch(test, 4, SearchPolicy::Last);                  // 6
    TestBinarySearch(test, 5);                                      // 7, 8, 9, 10, 11
    TestBinarySearch(test, 5, SearchPolicy::First);                 // 7
    TestBinarySearch(test, 5, SearchPolicy::Last);                  // 11
    TestBinarySearch(test, 7, SearchPolicy::FirstNotLessThan);      // 13
    TestBinarySearch(test, 7, SearchPolicy::LastNotGreatThan);      // 12
    TestBinarySearch(test, 7, SearchPolicy::First);                 // 14
    TestBinarySearch(test, 8);                                      // 13
    TestBinarySearch(test, 8, SearchPolicy::First);                 // 13
    TestBinarySearch(test, 8, SearchPolicy::Last);                  // 13

    return 0;
}