#include <iostream>
#include <atomic>
#include <mutex>

// 1. Hungry Mode
namespace hungryMode {
    class IdGenerator {
    public:
        std::shared_ptr<IdGenerator> getInstance() {
            return mInstance;
        }

        long getId() {
            return mId++;
        }

    private:
        std::atomic<long> mId{0};
        static std::shared_ptr<IdGenerator> mInstance;
    };

    std::shared_ptr<IdGenerator> IdGenerator::mInstance = std::make_shared<IdGenerator>();
}


// 2. Lazy Mode
namespace lazyMode {
    class IdGenerator {
    public:
        std::shared_ptr<IdGenerator> getInstance() {
            if (mInstance == nullptr) {
                mInstance = std::make_shared<IdGenerator>();
            }

            return mInstance;
        }

        long getId() {
            return mId++;
        }

    private:
        std::atomic<long> mId;
        static std::shared_ptr<IdGenerator> mInstance;
    };

    std::shared_ptr<IdGenerator> IdGenerator::mInstance = nullptr;
}


// 3. Double Check
namespace doubleCheck {
    class IdGenerator {
    public:
        std::shared_ptr<IdGenerator> getInstance() {
            if (mInstance == nullptr) {
                {
                    std::scoped_lock<std::mutex> lock(mMutex);

                    if (mInstance == nullptr) {
                        mInstance = std::make_shared<IdGenerator>();
                    }
                }
            }

            return mInstance;
        }

    private:
        std::mutex mMutex;
        std::atomic<long> mId;
        static std::shared_ptr<IdGenerator> mInstance;
    };

    std::shared_ptr<IdGenerator> IdGenerator::mInstance = nullptr;
}

// 4. Static Internal Class

// 5. Enumuration


/*
Disadvantages:
    1. Unfriendly support for OOP
    2. Hide the dependencies between classes
    3. Poor scalabiliry
    4. Poor testbility
    5. Unsupport constructor with paramters

Solution:
    1. Factory Design Pattern
    2. IOC container
    3. Programmer make sure do not creat more than one instance
*/

int main() {

    return 0;
}