/* Author: Jemmy
 * Date: 2020-03-25 */

#include <iostream>
#include <limits>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <optional>
#include <functional>

template<typename ValT>
class SkipList {
public:
    friend std::ostream& operator<<(std::ostream& os, const SkipList& list) {
        auto node = list.mHead->forwards[0];

        while (node != nullptr && node != list.mNil) {
            os << "Key: " << node->key << "\tValue: " << node->value << "\tLevel: " << list.getNodeLevel(node) << std::endl;
            node = node->forwards[0];
        }

        return os;
    }

    using value_type = ValT;
    using hash_type = std::hash<value_type>;
    using key_type = typename hash_type::result_type;
    using size_type = size_t;

public:
    SkipList() {
        auto headKey = std::numeric_limits<key_type>::min();
        auto nilKey = std::numeric_limits<key_type>::max();

        mHead = new node_type(headKey, mMaxLevel);
        mNil = new node_type(nilKey, mMaxLevel);
        std::fill(mHead->forwards.begin(), mHead->forwards.end(), mNil);
    }

    SkipList(std::initializer_list<value_type> list)
    :   SkipList() {
        for (auto& val : list)
            insert(val);
    }

    ~SkipList() {
        auto node = mHead;
        while (node != nullptr && node->forwards[0] != nullptr) {
            auto tmp = node;
            node = node->forwards[0];
            delete tmp;
        }
        delete node;
    }

    SkipList& operator=(const SkipList&) = delete;
    SkipList& operator=(SkipList&&) = delete;
    SkipList(const SkipList&) = delete;

    SkipList(SkipList&& other)
    :   mMaxLevel(std::move(other.mMaxLevel)),
        mProbability(std::move(other.mProbability)),
        mSeed(std::move(other.mSeed)),
        mEngine(std::move(other.mEngine)),
        mDistribution(std::move(other.mDistribution)),
        mHead(other.mHead),
        mNil(other.mNil)
    {
        other.mHead = nullptr;
        other.mNil = nullptr;
    }

    void insert(const value_type& value) {
        auto preds = getPredecessor(value);
        auto level = getRandomLevel();
        auto node = makeNode(value, level);

        for (size_type i = 0; i < level; ++i) {
            node->forwards[i] = preds[i]->forwards[i];
            preds[i]->forwards[i] = node;
        }
    }

    void erase(const value_type& value) {
        auto preds = getPredecessor(value);
        auto node = preds[0]->forwards[0];
        if (node == nullptr || node == mNil || node->value != value)
            return;

        for (size_type i = 0; i < getNodeLevel(node); ++i) {
            preds[i]->forwards[i] = node->forwards[i];
        }

        delete node;
    }

    using optional_type = std::optional<std::reference_wrapper<const value_type>>;
    optional_type find(const value_type& value) {
        auto key = mHasher(value);
        auto node = mHead;

        for (size_type i = getNodeLevel(mHead); i > 0; --i) {
            while (node->forwards[i-1]->key < key || (node->forwards[i-1]->key == key && node->forwards[i-1]->value != value)) {
                node = node->forwards[i-1];
            }
        }

        node = node->forwards[0];
        if (node != nullptr && node != mNil && node->value == value)
            return optional_type(value);
        else
            return std::nullopt;
    }

private:
    struct node_type;

    node_type* makeNode(const value_type& value, const size_type& level) {
        return new node_type(value, level);
    }

    size_type getRandomLevel() const {
        return mDistribution(mEngine);
    }

    size_type getNodeLevel(const node_type* node) const {
        return node->forwards.size();
    }

    std::vector<node_type*> getPredecessor(const value_type& value) {
        std::vector<node_type*> result(getNodeLevel(mHead), nullptr);

        auto key = mHasher(value);
        auto node = mHead;

        // size_t i = 0; --i // dead loop because i is std::numetic_limist<sizt_t>::max()
        for (size_type i = getNodeLevel(mHead); i > 0; --i) {
            while (node->forwards[i-1]->key < key || (node->forwards[i-1]->key == key && node->forwards[i-1]->value != value)) {
                node = node->forwards[i-1];
            }

            result[i-1] = node;
        }

        return result;
    }

private:
    struct node_type {
        const key_type key;
        value_type value;
        std::vector<node_type*> forwards;

        // key(mHasher(value)) doesn't work?
        node_type(const value_type& value, const size_type& level)
        :   key(hash_type()(value)), value(value), forwards(level, nullptr)
        { }

        node_type(const key_type& key, const size_type& level)
        :   key(key), value(), forwards(level, nullptr)
        { }
    };

    const size_type mMaxLevel = 16;
    const double mProbability = 0.5;

    // 'auto' not allowed in non-static class member
    const unsigned int mSeed = std::chrono::system_clock::now().time_since_epoch().count();

    // Mutable is used to specify that the member does not affect the externally visible state of the class.
    mutable std::default_random_engine mEngine = std::default_random_engine(mSeed);

    mutable std::binomial_distribution<size_type> mDistribution = std::binomial_distribution<size_type>(mMaxLevel-1, mProbability);

    hash_type mHasher = hash_type();
    node_type* mHead = nullptr;
    node_type* mNil = nullptr;
};

int main() {
    // 1. Initialize a skip list for test
    // * default constructor
    // * constructor with initializer list
    // * insert
    SkipList<std::string> list{"1", "2", "3", "4", "5"};

    // 1a. show
    // * print
    std::cout << list << std::endl;

    // 2. move construction
    // * move constructor
    SkipList<std::string> li(std::move(list));

    // 2a. show
    // * print
    std::cout << li << std::endl;

    // 3.a find something doesn't exist.
    // * find
    auto f = li.find("0");
    if (f) {
        std::cout << "Node found!\nvalue: " << (*f).get() << '\n';
    } else {
        std::cout << "Node NOT found!\n";
    }

    // 3.b find something does exist.
    // * find
    auto ff = li.find("1");
    if (ff) {
        std::cout << "Node found!\tvalue: " << (*ff).get() << '\n';
    } else {
        std::cout << "Node NOT found!\n";
    }

    // 4. insert() - reassign
    li.insert("TEST");

    // 4a. print()
    std::cout << li << std::endl;

    // 5. erase()
    li.erase("TEST");

    // 5a. print();
    std::cout << li << std::endl;

    std::cout << "Done!" << std::endl;

    return 0;
    // 6. destructor
}
