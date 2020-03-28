#include <iostream>
#include <stdexcept>

template<typename T, size_t Size>
class CircularQueue {
public:
    friend std::ostream& operator<<(std::ostream& os, const CircularQueue& queue) {
        for (auto i = queue.mHead; i < queue.mTail; ++i) {
            std::cout << queue.mQueue[i] << " ";
        }

        return os;
    }

public:
    CircularQueue() : mSize(Size) {
        mQueue = new T[mSize];
    }

    ~CircularQueue() {
        if (mQueue != nullptr) {
            delete[] mQueue;
            mQueue = nullptr;
        }
    }

    CircularQueue(const CircularQueue& rhs) : mSize(rhs.mSize) {
        mQueue = new T[mSize];
        for (size_t i = rhs.mHead; i != rhs.mTail; i = (i+1)%rhs.mSize) {
            push(rhs.mQueue[i]);
        }
    }

    CircularQueue(CircularQueue&& rhs)
    :   mSize(rhs.mSize), mQueue(rhs.mQueue), mHead(rhs.mHead), mTail(rhs.mTail)
    {
        rhs.mHead = 0;
        rhs.mTail = 0;
        rhs.mSize = 0;
        rhs.mQueue = nullptr;
    }

    CircularQueue& operator=(const CircularQueue& rhs) {
        if (this != &rhs) {
            reset();

            mSize = rhs.mSize;
            mQueue = new T[mSize];
            for (size_t i = rhs.mHead; i != rhs.mTail; i = (i+1)%rhs.mSize) {
                push(rhs.mQueue[i]);
            }
        }

        return *this;
    }

    CircularQueue& operator=(CircularQueue&& rhs) {
        if (this != &rhs) {
            reset();

            mSize = rhs.mSize;
            mHead = rhs.mHead;
            mTail = rhs.mTail;
            mQueue = rhs.mQueue;

            rhs.reset();
        }

        return *this;
    }

    void push(T data) {
        if ((mTail+1)%mSize == mHead)
            throw std::out_of_range("The Queue is full!");

        mQueue[mTail] = data;
        mTail = (mTail+1)%mSize;
    }

    T pop() {
        if (mHead == mTail)
            throw std::out_of_range("The Queue is already empty!");

        T data = mQueue[mHead];
        mHead = (mHead+1)%mSize;

        return data;
    }

private:
    void reset() {
        delete[] mQueue;
        mQueue = nullptr;
        mSize = 0;
        mHead = 0;
        mTail = 0;
    }

private:
    T* mQueue{nullptr};
    size_t mSize{0};
    size_t mHead{0};
    size_t mTail{0};
};

int main() {
    CircularQueue<int, 5> queue;

    try {
        for (auto i = 0; i < 5; ++i) {
            queue.push(i);
            std::cout << queue << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    CircularQueue<int, 5> queue2(queue);
    std::cout << "queue: " << queue << std::endl;
    std::cout << "[2 copy() 1] queue2: " << queue2 << std::endl;

    CircularQueue<int, 5> queue3(std::move(queue));
    std::cout << "[3 move() 1] queue3: " << queue3 << std::endl;
    std::cout << "queue: " << queue << std::endl;

    queue3 = queue3;
    std::cout << "[3 copy = 3] queue3: " << queue3 << std::endl;
    queue3 = std::move(queue3);
    std::cout << "[3 move = 3] queue3: " << queue3 << std::endl;

    CircularQueue<int, 5> queue4 = queue3;
    std::cout << "[4 copy = 3] queue4: " << queue4 << std::endl;

    CircularQueue<int, 5> queue5 = std::move(queue3);
    std::cout << "[5 move = 3] queue5: " << queue5 << std::endl;
    std::cout << "queue3: " << queue3 << std::endl;


    try {
        for (auto i = 0; i < 5; ++i) {
            queue.pop();
            std::cout << queue << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}