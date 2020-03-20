/* Author: Jemmy
 * Time: 2020-03-20 */

#include <iostream>
#include <vector>
#include <algorithm>

template<size_t bucketSize,
    typename Ite,
    typename T = typename std::iterator_traits<Ite>::value_type,
    typename Comparator = std::less<T>>
void bucketSort(Ite begin, Ite end, Comparator comparator = Comparator()) {
    const T min = *std::min_element(begin, end);
    const T max = *std::max_element(begin, end);
    const T range = max - min + 1;
    const size_t bucketNumber = (range - 1) / bucketSize + 1;

    std::vector<std::vector<T>> buckets(bucketNumber);
    for (auto& b : buckets) {
        b.reserve(2 * bucketSize);
    }

    for (auto ite = begin; ite != end; ++ite) {
        auto idx = (*ite - min) / bucketSize;
        buckets[idx].emplace_back(*ite);
    }

    auto dest = begin;
    for (auto& b : buckets) {
        std::sort(b.begin(), b.end(), comparator);
        std::copy(b.begin(), b.end(), dest);
        dest += b.size();
    }
}


int main() {
    std::vector<int> data{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};

    bucketSort<2>(data.begin(), data.end());
    std::transform(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "),
            [](const auto& data){ return data; });
    std::cout << std::endl;

    bucketSort<3>(data.begin(), data.end());
    std::transform(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "),
            [](const auto& data){ return data; });
    std::cout << std::endl;

    bucketSort<4>(data.begin(), data.end());
    std::transform(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "),
            [](const auto& data){ return data; });
    std::cout << std::endl;


    bucketSort<5>(data.begin(), data.end());
    std::transform(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "),
            [](const auto& data){ return data; });
    std::cout << std::endl;

    return 0;
}