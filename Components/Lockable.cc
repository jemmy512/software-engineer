#include <mutex>
#include <string>
#include <vector>
#include <iostream>

template<typename T>
class Lockable {
private:
    mutable std::recursive_mutex mMutex;
    T mData;

public:
    class Ptr {
    public:
        explicit Ptr(Lockable* lockable) : mLockable(lockable), mLock(lockable->mMutex) {}

        Ptr(Ptr&& other) : mLockable(other.mLockable), mLock(std::move(other.mLock)) {
            other.mLockable = nullptr;
        }

        Ptr(const Ptr&) = delete;

        Ptr& operator==(const Ptr&) = delete;

        T* operator->() {
            if (mLockable) {
                return &mLockable->mData;
            }

            return nullptr;
        }

        T& operator*() {
            if (mLockable) {
                return mLockable->mData;
            }

            throw("Error");
        }

        operator bool() {
            return mLockable != nullptr;
        }

    private:
        Lockable *mLockable;
        std::unique_lock<std::recursive_mutex> mLock;
    };

    class ConstPtr {
    public:
        explicit ConstPtr(const Lockable* lockable) : mLockable(lockable), mLock(lockable->mMutex) {}

        ConstPtr(ConstPtr&& other) : mLockable(other.mLockable), mLock(std::move(other.mMutex)) {
            other.mLockable = nullptr;
        }

        ConstPtr(const ConstPtr&) = delete;

        ConstPtr& operator==(const ConstPtr&) = delete;

        const T* const operator->() {
            if (mLockable) {
                return &mLockable->mData;
            }

            return nullptr;
        }

        const T& operator*() {
            if (mLockable) {
                return mLockable->mData;
            }

            throw("Errro");
        }

        operator bool() {
            return mLockable != nullptr;
        }

    private:
        const Lockable* mLockable;
        std::unique_lock<std::recursive_mutex> mLock;
    };

public:
    template<typename... Args>
    explicit Lockable(Args... args) : mData(args...) {}

    Ptr lock() {
        // return std::move(Ptr(this));
        return Ptr(this); // return copy elision
    }

    ConstPtr readLock() const {
        return ConstPtr(this);
    }
};

 void foo() {
    std::string str = "Hello world!";
    std::vector<std::string> vecString;
    std::cout<< "1. " << std::dec << (long)&str << ", " << std::dec << (long)&str[0] << ", " << str << std::endl;

    vecString.push_back(std::move(str));

    std::cout << "2. " << std::dec << (long)&str << ", " << std::dec << (long)&str[0] << ", " << str << std::endl;

    str.append("w");
    std::cout << "3. " << std::dec << (long)&str << ", " << std::dec << (long)&str[0] << ", " << str << std::endl;

    std::cout<< "4. " << std::dec << (long)&(vecString[0]) << ", " << std::dec <<  (long)&(vecString[0][0]) << ", " << std::dec << (long)&vecString << std::endl;
}

class AB {
public:
    AB(){
        std::cout << "constructor" << std::endl;
    }
    AB(const AB& rhs) : age(rhs.age), name(rhs.name) {
        std::cout << "copy constructor" << std::endl;
    }

    AB(AB&& ab) : age(std::move(ab.age)), name(std::move(ab.name)) {
        std::cout << "move constructor" << std::endl;
    }

    ~AB() {
        std::cout << "~()" << std::endl;
    }

    int age = 23;
    std::string name = "name";
};