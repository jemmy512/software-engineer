#include <iostream>
#include <vector>
#include <mutex>

class IMessageObserver {
public:
    virtual void onDelete(const std::string& msg) = 0;
    virtual void onSend(const std::string& msg, int id) = 0;
    virtual ~IMessageObserver() = default;
};

template<typename Observer>
class Notification {
public:
    using ObserverWPtr = std::weak_ptr<Observer>;
    using ObserverPtr = std::shared_ptr<Observer>;
    using ObserverList = std::vector<ObserverWPtr>;

    void registerObserver(ObserverPtr observer) {
        std::scoped_lock lock(mMutex);

        if (findObserver(observer) == mObservers.cend()) {
            mObservers.emplace_back(observer);
        }
    }

    void unregisterObserver(ObserverPtr observer) {
        std::scoped_lock lock(mMutex);

        mObservers.erase(findObserver(observer));
    }

    template<typename Func, typename... Args>
    void notify(Func func, Args&&... args) {
        ObserverList liveObservers;
        liveObservers.reserve(mObservers.size());

        for (const auto& wob : mObservers) {
            if (auto ob = wob.lock()) {
                std::invoke(func, ob, std::forward<Args>(args)...);

                liveObservers.emplace_back(wob);
            }
        }

        removeExpiredObservers(std::move(liveObservers));
    }

private:
    auto findObserver(ObserverPtr observer) {
        return std::find_if(mObservers.cbegin(), mObservers.cend(), [observer](auto& wob) {
                if (auto ob = wob.lock()) {
                    return ob == observer;
                } else {
                    return false;
                }
            });
    }

    /**
     * std::weak_ptr doesn't suppport compare operation, there's no way to get the
     * iterator of a weak_ptr and then use erase to delete it from vector.
     *
     * auto ite = std::remove_if(mObservers.begin(), mObservers.end(), [](const auto& wob){
     *  return (auto ob = wob.lock()) ? true : false;
     * });
     * mObservers.erase(ite, mObservers.end());
     */
    void removeExpiredObservers(ObserverList&& liveObservers) {
        std::scoped_lock lock(mMutex);

        if (liveObservers.size() < mObservers.size() / 3) {
            mObservers = std::move(liveObservers);
        }
    }

private:
    std::mutex mMutex;
    ObserverList mObservers;
};

class MessageManager : public IMessageObserver {
public:
    void onDelete(const std::string& msg) override {
        std::cout << "ON delete observer msg: " << msg << std::endl;
    }

    void onSend(const std::string& msg, int id) override {
        std::cout << "ON Send observer msg: " << msg << ", id: " << id << std::endl;
    }
};

class Server : public Notification<IMessageObserver> {
public:
    Server() {
        mMsgManager = std::make_shared<MessageManager>();

        registerObserver(mMsgManager);
    }
    void deleteMessage(const std::string& msg)  {
        notify(&IMessageObserver::onDelete, msg);
    }

    void sendMessage(const std::string& msg, int id) {
        notify(&IMessageObserver::onSend, "msg", id);
    }

private:
    std::shared_ptr<MessageManager> mMsgManager;
};

int main() {
    Server server;

    server.deleteMessage("You delted your message.");
    server.sendMessage("Alice sent a message to Bob", 1238);
}
