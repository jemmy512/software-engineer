#include <iostream>
#include <list>
#include <mutex>

class IMessageObserver {
public:
    virtual void onDelete(const std::string& msg) = 0;
    virtual void onSend(const std::string& msg, int id) = 0;
    virtual ~IMessageObserver() = default;
};

template<typename Observer>
class Notifier {
public:
    using ObserverWPtr = std::weak_ptr<Observer>;
    using ObserverPtr = std::shared_ptr<Observer>;
    using ObserverList = std::list<ObserverWPtr>;

    void registerObserver(ObserverPtr observer) {
        std::scoped_lock lock(_Mutex);

        if (findObserver(observer) == _Observers.cend()) {
            _Observers.emplace_back(observer);
        }
    }

    void unregisterObserver(ObserverPtr observer) {
        std::scoped_lock lock(_Mutex);

        _Observers.remove_if([target = observer](const auto& weakObserver) {
            const auto observer = weakObserver.lock();
            return observer && observer == target;
        })
    }

    template<typename Func, typename... Args>
    void notify(Func func, Args&&... args) {
        _Observers.remove_if([](const auto& weakObserver) {
            return weakObserver.lock() == nullptr;
        });

       for (const auto& weakObserver : _Observers) {
            if (auto observer = weakObserver.lock()) {
                std::invoke(func, observer, std::forward<Args>(args)...);
            }
        }
    }

private:
    auto findObserver(ObserverPtr target) {
        return std::find_if(_Observers.cbegin(), _Observers.cend(), [&target](const auto& weakObserver) {
            if (auto observer = weakObserver.lock()) {
                return observer == target;
            } else {
                return false;
            }
        });
    }

    /**
     * std::weak_ptr doesn't suppport compare operation, there's no way to get the
     * iterator of a weak_ptr and then use erase to delete it from vector.
     *
     * auto ite = std::remove_if(_Observers.begin(), _Observers.end(), [](const auto& weakObserver){
     *  return (auto ob = weakObserver.lock()) ? true : false;
     * });
     * _Observers.erase(ite, _Observers.end());
     */
    void removeExpiredObservers(ObserverList&& liveObservers) {
        std::scoped_lock lock(_Mutex);

        if (liveObservers.size() < _Observers.size() / 3) {
            _Observers = std::move(liveObservers);
        }
    }

private:
    std::mutex _Mutex;
    ObserverList _Observers;
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

class Server : public Notifier<IMessageObserver> {
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
