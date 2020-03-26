#include <iostream>
#include <stdexcept>

class CircularQueue {
public:
    CircularQueue(int size) : mSize(size) {
        mQueue = new int[mSize];
    }

    bool enqueue(int data) {
        if ((mTail+1)%mSize == mHead)
            return false;
            
        mQueue[mTail] = data;
        mTail = (mTail+1)%mSize;

        return true;
    }

    int dequeue() {
        if (mHead == mTail)
            throw std::out_of_range("The Queue is already empty!");
        
        int data = mQueue[mHead];
        mHead = (mHead+1)%mSize;

        return mHead;
    }

private:
    int* mQueue{nullptr};
    int mSize{0};
    int mHead{0};
    int mTail{0};
};

int main() {
    CircularQueue queue(10);

    try {
        queue.dequeue();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}