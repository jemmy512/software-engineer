/* Author: Jemmy
 * Date: 2020-03-20 */

#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <list>

/* 1. Define Strategy */
enum class SortEnum {
    QuickSort,
    InsertSort
};

template<typename Iter>
class ISort {
public:
    virtual void sort(Iter begin, Iter end) = 0;
    virtual ~ISort() = default;
};

template<typename Iter>
class QuickSort : public ISort<Iter> {
public:
    void sort(Iter begin, Iter end) override {
        std::cout << "~ Quick Sort" << std::endl;
    }
};

template<typename Iter>
class InsertSort : public ISort<Iter> {
public:
    void sort(Iter begin, Iter end) override {
        std::cout << "+ Insert Sort" << std::endl;
    }
};

/* 2. Create Strategy */
template<typename Iter>
class SortFactory {
public:
    using SortPtr = std::shared_ptr<ISort<Iter>>;

public:
    static SortPtr getAlgorithm(const SortEnum& type);
    static inline std::map<SortEnum, SortPtr> sortAlgorithmes;

};

// template<typename Iter>
// SortFactory<Iter>::sortAlgorithmes.emplace("QuickSort", std::make_shared<QuickSort<Iter>>());

// SortFactory::sortAlgorithmes.emplace_back("QuickSort", std::make_shared<QuickSort>());
// sortAlgorithmes.emplace_back("QuickSort", std::make_shared<QuickSort>());

// sorsortAlgorithmests.emplace_back("QuickSort", std::make_shared<QuickSort>());


template<typename Iter>
typename SortFactory<Iter>::SortPtr
SortFactory<Iter>::getAlgorithm(const SortEnum& type) {
    auto iter = sortAlgorithmes.find(type);
    if (iter == sortAlgorithmes.end()) {
        if (type == SortEnum::QuickSort)
            sortAlgorithmes.emplace(type, std::make_shared<QuickSort<Iter>>());
        else if (type == SortEnum::InsertSort)
            sortAlgorithmes.emplace(type, std::make_shared<InsertSort<Iter>>());
    }

    return sortAlgorithmes[type];
}

/* 3. Use Strategy */
int main() {
    std::vector<int> data{3, 2, 5, 8, 4, 7, 6, 9, 1};
    std::list<int> dataList{2, 3, 5, 8, 4, 7, 6, 1, 9};

    using VecIter = std::vector<int>::iterator;
    auto quickSort = SortFactory<VecIter>::getAlgorithm(SortEnum::QuickSort);
    quickSort->sort(data.begin(), data.end());

    using ListIter = std::list<int>::iterator;
    auto insertSort = SortFactory<ListIter>::getAlgorithm(SortEnum::InsertSort);
    insertSort->sort(dataList.begin(), dataList.end());

    return 0;
}

/**
 * Define a family of algorithms, encapsulate each one, and make them interchangeable.
 * Strategy lets the algorithm vary independently from clients that use it. */