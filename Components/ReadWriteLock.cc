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

class sharedLock {
public:
    sharedLock(ReadWriteLock& lock) : mLock(lock) {
        mLock.lockRead();
    }

    ~sharedLock() {
        mLock.unlockRead();
    }

private:
    ReadWriteLock& mLock;
};

class uniqueLock {
public:
    uniqueLock(ReadWriteLock& lock) : mLock(lock) {
        mLock.lockWrite();
    }

    ~uniqueLock() {
        mLock.unlockWrite();
    }

private:
    ReadWriteLock& mLock;
};