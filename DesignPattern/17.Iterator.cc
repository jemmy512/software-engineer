#include <iostream>
#include <chrono>
#include <optional>

using time_point = std::chrono::system_clock::time_point;
using optional_time_point = std::optional<std::chrono::system_clock::time_point>;

template<typename T>
struct Node {
    T data;
    optional_time_point ctime; // creat time
    optional_time_point dtime; // delet time
};


template<typename T, typename Node = Node<T>>
class Vector {
public:
    ~Vector() {
        delete[] mData;
    }

    void push_back(const T& val) {
        if (mSize + 1 >= mCapacity) {
            expand();
        }

        mData[mSize++] = {val, optional_time_point(std::chrono::system_clock::now()), optional_time_point()};
    }

    void erase(const T& val) {
        for (auto i = 0; i < mSize; ++i) {
            auto& v = mData[i];
            if (v.data == val) {
                v.dtime = std::chrono::system_clock::now();
                ++mExpired;

                return;
            }
        }
    }

    void clearExpired(time_point time) {
        if (staic_cast<double>(mExpired) / mSize >= 0.75) {
            auot newSize = mSize;
            bool deleted = false;

            for (auto i =0; i < mSize; ++i) {
                const auto& node = mData[i];
                if (deleted) {
                    if (node.dtime && node.dtime < time) {
                        --newSize;
                    }

                    mData[i-1] = std::move(mData[i]);
                } else {
                    if (node.dtime && node.dtime < time) {
                        mData[i] = std::move(mData[i+1]);
                        --newSize;
                        ++i;
                        deleted = true;
                    }
                }
            }
        }
    }

private:
    void expand() {
        mCapacity *= 2;
        Node<T>* tmp  = new Node<T>[mCapacity]();

        for (auto i = 0; i < mSize; ++i) {
            tmp[i] = mData[i];
        }

        delete[] mData;
        mData = tmp;
    }

private:
    int mSize = 0;
    int mExpired = 0;
    int mCapacity = 16;
    Node<T>* mData = nullptr;
};


template<typename Container>
class Iterator {
public:

private:
    Container& mContainer;
};

int main() {

    return 0;
}