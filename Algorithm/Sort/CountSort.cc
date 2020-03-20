/* Author: Jemmy
 * Time: 2020-03-20 */

#include <iostream>
#include <vector>
#include <algorithm>

// stable sort
template<typename Iter, typename T = typename std::iterator_traits<Iter>::value_type>
void countSort(Iter begin, Iter end) {
    int len = std::distance(begin, end);
    if (len < 2)
        return;

    auto max = *std::max_element(begin, end);
    if (max < 0)
        return;

    std::vector<T> counters(max+1);
    for (auto ite = begin; ite != end; ++ite) {
        ++counters[*ite];
    }

    for (auto idx = max-1; idx >= 0; --idx) {
        counters[idx] += counters[idx+1];
    }

    std::vector<T> tmp(len, -2);
    for (auto ite = begin; ite != end; ++ite) {
        tmp[len-counters[*ite]] = *ite;
        --counters[*ite];
    }

    std::copy(tmp.begin(), tmp.end(), begin);
}

// unstable sort
template<typename Iter, typename T = typename std::iterator_traits<Iter>::value_type>
void _countSort(Iter begin, Iter end) {
    auto len = std::distance(begin, end);
    if (len < 2)
        return;

    auto max = *std::max_element(begin, end);
    if (max < 0)
        return;

    std::vector<T> counters(max+1);
    for (auto ite = begin; ite != end; ++ite) {
        ++counters[*ite];
    }

    for (auto idx = 1; idx < max+1; ++idx) {
        counters[idx] += counters[idx-1];
    }

    std::vector<T> tmp(len, -1);
    for (auto ite = begin; ite != end; ++ite) {
        tmp[counters[*ite]-1] = *ite;
        --counters[*ite];
    }

    std::copy(tmp.begin(), tmp.end(), begin);
}

int main() {
    std::vector<int> data1{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};
    countSort(data1.begin(), data1.end());
    std::transform(data1.begin(), data1.end(), std::ostream_iterator<int>(std::cout, " "),
            [](auto& data){ return data; });
    std::cout << std::endl;

    std::vector<int> data2{2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9};
    countSort(data2.begin(), data2.end());
    std::transform(data2.begin(), data2.end(), std::ostream_iterator<int>(std::cout, " "),
            [](auto& data){ return data; });
    std::cout << std::endl;


    std::vector<int> data3{5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9};
    countSort(data3.begin(), data3.end());
    std::transform(data3.begin(), data3.end(), std::ostream_iterator<int>(std::cout, " "),
            [](auto& data){ return data; });
    std::cout << std::endl;


    std::vector<int> data4{3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4};
    countSort(data4.begin(), data4.end());
    std::transform(data4.begin(), data4.end(), std::ostream_iterator<int>(std::cout, " "),
            [](auto& data){ return data; });
    std::cout << std::endl;


    std::vector<int> data5{5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6, 2, 8, 6};
    countSort(data5.begin(), data5.end());
    std::transform(data5.begin(), data5.end(), std::ostream_iterator<int>(std::cout, " "),
            [](auto& data){ return data; });
    std::cout << std::endl;

    return 0;
}