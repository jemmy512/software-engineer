#include <iostream>
#include <chrono>
#include <mutex>
#include <functional>
#include <set>
#include <atomic>
#include <thread>
#include <unordered_map>

#define Print(x) std::cout << (x) << std::endl;

class TimerManager;

class Timer {
public:
    Timer(TimerManager::TimerId id, const std::weak_ptr<TimerManager>& manager)
    :   mId(id), mManager(manager) {}

    Timer(const Timer&) = delete;

    Timer(Timer&& other) noexcept : mId (other.mId), mManager(other.mManager) {}

    Timer& operator=(Timer&& other) noexcept {
        if (this != & other) {
            mId = other.mId;
            mManager = other.mManager;

            other.mId = -1;
            other.mManager.reset();
        }

        return *this;
    }

    ~Timer() {
        if (auto locked = mManager.lock()) {
            locked->destory(mId);
        }
    }

    bool isActive() {
        bool isActive = false;

        if (auto locked = mManager.lock()) {
            isActive = locked->isActive(mId);
        }

        return isActive;
    }

    TimerManager::TimerId getId() const {
        return mId;
    }

    static Timer createTimer(TimerManager::TimerId id, const std::weak_ptr<TimerManager>& manager) {
        return Timer{id, manager};
    }

private:
    std::mutex mMutex{};
    TimerManager::TimerId mId;
    std::weak_ptr<TimerManager> mManager;
};

class TimerManager : public std::enable_shared_from_this<TimerManager> {
public:
    using TimerId = uint64_t;
    using Clock  = std::chrono::steady_clock;
    using TimeStamp = std::chrono::time_point<Clock>;
    using Duration = std::chrono::milliseconds;
    using TimerFunc = std::function<void()>;

public:
    TimerManager()
    :   mNextId(-1), mOrderedTimers(timerComparator), mDone(false)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mThread = std::thread(&TimerManager::start, this);
        mThreadId = mThread.get_id();
    }

    Timer creatTimer(uint16_t when, Duration period, TimerFunc&& func) {
        std::unique_lock<std::mutex> lock(mMutex);

        auto&& timer = TimerEntry(++mNextId, Clock::now() + Duration(when), Duration(period), std::move(func));
        auto ite = mTimers.emplace(mNextId, std::move(timer));
        mOrderedTimers.emplace(ite.first->second);
        mSignal.notify_one();

        return Timer::createTimer(mNextId, weak_from_this());
    }

    bool destory(TimerId id) {
        std::unique_lock<std::mutex> lock(mMutex);

        auto ite = mTimers.find(id);
        if (ite == mTimers.end()) {
            return false;
        } else {
            ite->second.mIsDestroyed = true;
            mSignal.notify_all();
            return true;
        }
    }

    bool isActive(TimerId id) {
        std::unique_lock<std::mutex> lock(mMutex);

        return mTimers.find(id) != mTimers.end();
    }

    void fireNow(TimerId id) {

    }

    ~TimerManager() {
        try {
            std::unique_lock<std::mutex> lock(mMutex);

            mDone = true;
            mSignal.notify_all();
            lock.unlock();
            mThread.join();
        } catch (const std::exception& e) {
            Print(e.what());
        }
    }

private:
    struct TimerEntry {
        TimerEntry(TimerId id, TimeStamp next, Duration period, TimerFunc&& func)
        :   mId(id), mNext(next), mPeriod(period), mHandler(std::forward<TimerFunc>(func)) {
            Print(std::string{"TimerEntry() "} + std::string{"Id: "} + std::to_string(mId));
        }

        TimerEntry(TimerEntry&& other)
        :   mId(other.mId), mNext(other.mNext), mPeriod(other.mPeriod), mHandler(std::move(other.mHandler)) {
            Print(std::string{"TimerEntry(&&) "} + std::string{"Id: "} + std::to_string(mId));
        }

        TimerEntry& operator=(TimerEntry&& other) {
            if (this != &other) {
                mId = other.mId;
                mNext = other.mNext;
                mPeriod = other.mPeriod;
                mHandler = std::move(other.mHandler);
            }

            Print(std::string{"TimerEntry=(&&) "} + std::string{"Id: "} + std::to_string(mId));
            return *this;
        }

        TimerEntry(const TimerEntry&) = delete;
        TimerEntry& operator=(const TimerEntry&) = delete;

        TimerId mId;
        TimeStamp mNext;
        Duration mPeriod;
        TimerFunc mHandler;
        bool mIsDestroyed{false};
    };

    void start() {
        std::unique_lock<std::mutex> lock(mMutex);

        while (!mDone) {
            if (!mOrderedTimers.empty()) {
                auto timerIte = mOrderedTimers.begin();
                TimerEntry& timer = *timerIte;

                auto now = Clock::now();
                if (now >= timer.mNext) {
                    mOrderedTimers.erase(timerIte);

                    if (!timer.mIsDestroyed) {
                        auto handlerWrapper = [hanlder(timer.mHandler)]() {
                            try {
                                hanlder();
                            } catch (const std::exception& e) {
                                Print(e.what());
                            }
                        };

                        handlerWrapper();

                        // mThreadPool.dispatch(handlerWrapper);

                        if (timer.mPeriod.count() > 0) {
                            timer.mNext += timer.mPeriod;
                            now = Clock::now();
                            if (now >= timer.mNext) {
                                timer.mNext = now + timer.mPeriod;
                            }

                            mOrderedTimers.insert(timer);
                        } else {
                            mTimers.erase(timer.mId);
                        }

                    } else {
                        mTimers.erase(timer.mId);
                    }

                } else {
                    mSignal.wait_until(lock, timer.mNext);
                }
            } else {
                mSignal.wait(lock);
            }
        }
    }

    std::function<bool(const TimerEntry&, const TimerEntry&)> timerComparator = [](const TimerEntry& lhs, const TimerEntry& rhs) {
        return lhs.mNext < rhs.mNext;
    };
    using TimerMap = std::unordered_map<TimerId, TimerEntry>;
    using OrderedTimers = std::multiset<std::reference_wrapper<TimerEntry>, decltype(timerComparator)>;

    TimerId mNextId;
    TimerMap mTimers;
    OrderedTimers mOrderedTimers;
    std::condition_variable mSignal;
    std::mutex mMutex;

    std::thread mThread;
    std::atomic<std::thread::id> mThreadId;
    std::atomic<bool> mDone;
};


int main() {

    auto manager = std::make_shared<TimerManager>();

    auto timerAlice = manager->creatTimer(1000, std::chrono::milliseconds{1000}, [](){
        Print("1");
    });

    auto timerBob = manager->creatTimer(4000, std::chrono::milliseconds{1500}, [](){
        Print("2");
    });

    // Print(manager.isActive(id1));
    // Print(manager.isActive(id2));

    std::this_thread::sleep_for(std::chrono::milliseconds{5000});
    manager->destory(timerAlice.getId());

    std::this_thread::sleep_for(std::chrono::milliseconds{35000});

    return 0;
}
