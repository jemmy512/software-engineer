#include <mutex>
#include <iostream>

class ReadWriteLock {
public:
    ReadWriteLock(const ReadWriteLock&) = delete;
    ReadWriteLock& operator=(const ReadWriteLock&) = delete;

    void lockRead() {
        mReadMutex.lock();
        if (++mReaders == 1)
            mWriteMutex.lock();
        mReadMutex.unlock();
    }

    void unlockRead() {
        mReadMutex.lock();
        if (--mReaders == 1)
            mWriteMutex.unlock();
        mReadMutex.unlock();
    }

    void lockWrite() {
        mWriteMutex.lock();
    }

    void unlockWrite() {
        mWriteMutex.unlock();
    }

private:
    std::mutex mReadMutex;
    std::mutex mWriteMutex;
    int mReaders{0};
};

class SharedLock {
public:
    SharedLock(ReadWriteLock& lock) : mLock(lock) {
        mLock.lockRead();
    }

    ~SharedLock() {
        mLock.unlockRead();
    }

private:
    ReadWriteLock& mLock;
};

class UniqueLock {
public:
    UniqueLock(ReadWriteLock& lock) : mLock(lock) {
        mLock.lockWrite();
    }

    ~UniqueLock() {
        mLock.unlockWrite();
    }

private:
    ReadWriteLock& mLock;
};