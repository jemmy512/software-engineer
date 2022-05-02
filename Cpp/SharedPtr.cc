#include <iostream>
#include <mutex>

template<class T>
class SharedPtr{
public:
    SharedPtr(T* ptr = nullptr)
    : Ptr(ptr), RefCount(new int(1)), Mutex(new mutex()) { }

    ~SharedPtr() {
        release();
    }

    SharedPtr(const SharedPtr<T>& sp)
    : Ptr(sp.Ptr), RefCount(sp.RefCount), Mutex(sp.Mutex) {
        addRefCount();
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& sp) {
        if (Ptr != sp.Ptr) {
            release();
            Ptr = sp.Ptr;
            RefCount = sp.RefCount;
            Mutex = sp.Mutex;
            addRefCount();
        }

        return *this;
    }

    T& operator*() {
        return *Ptr;
    }

    T* operator->() {
        return Ptr;
    }

    int useCount() const { return *RefCount; }

    T* get() { return Ptr; }

    void addRefCount() {
        Mutex->lock();
        ++(*RefCount);
        Mutex->unlock();
    }

private:
    void release() {
        bool deleteflag = false;

        Mutex->lock();
        if (--(*RefCount) == 0) {
            delete RefCount;
            delete Ptr;
            deleteflag = true;
        }
        Mutex->unlock();

        if (deleteflag)
            delete Mutex;
    }

private:
    int* RefCount = nullptr;
    T* Ptr = nullptr;
    std::mutex* Mutex = nullptr;
};