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
    static std::map<SortEnum, SortPtr> sortAlgorithmes;

};

template<typename Iter>
std::map<SortEnum, typename SortFactory<Iter>::SortPtr> SortFactory<Iter>::sortAlgorithmes = {
    {SortEnum::QuickSort, std::make_shared<QuickSort<Iter>>()},
    {SortEnum::InsertSort, std::make_shared<InsertSort<Iter>>()}
};

template<typename Iter>
typename SortFactory<Iter>::SortPtr
SortFactory<Iter>::getAlgorithm(const SortEnum& type) {
    auto iter = sortAlgorithmes.find(type);
    if (iter == sortAlgorithmes.end()) {
        if (type == SortEnum::QuickSort)
            sortAlgorithmes.emplace(type, std::make_shared<QuickSort<Iter>>());
        else if (type == SortEnum::InsertSort)
            sortAlgorithmes.emplace(type, std::make_shared<InsertSort<Iter>>());
        else
            throw std::invalid_argument("Don't support this type!");
    }

    return sortAlgorithmes[type];
}

template<typename Iter>
typename SortFactory<Iter>::SortPtr
SortFactory<Iter>::getAlgorithm(const SortEnum& type) {
    return sortAlgorithmes.at(type);
}

/* 3. Use Strategy */
int main() {
    std::vector data{3, 2, 5, 8, 4, 7, 6, 9, 1};
    std::list dataList{2, 3, 5, 8, 4, 7, 6, 1, 9};

    auto quickSort = SortFactory<decltype(data)::iterator>::getAlgorithm(SortEnum::QuickSort);
    quickSort->sort(data.begin(), data.end());

    auto insertSort = SortFactory<decltype(dataList)::iterator>::getAlgorithm(SortEnum::InsertSort);
    insertSort->sort(dataList.begin(), dataList.end());

    return 0;
}

/**
 * Define a family of algorithms, encapsulate each one, and make them interchangeable.
 * Strategy lets the algorithm vary independently from clients that use it.
 *
 * Strategy decouples the definition, creation and usage of a strategy, avoid complexity of each part.
 *
 * * Strategy VS Command:
 * 1. A group Strategies have the same goal, but different implementation, they can interexchange
 * 2. A group commands have different goals, and they can't interexchange
 *
 *
 * Strategy VS Factory:
 * 1. Strategy focus on strategies or algorithms, select different strategies according to different scenarios
 * 2. Factory focus on the creation of objects, regardless of scenarios */