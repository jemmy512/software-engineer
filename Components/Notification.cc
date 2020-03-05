#include <iostream>
#include <vector>
#include <mutex>

class IMessageCallback {
public:
    virtual void onDelete(const std::string& msg) = 0;
    virtual void onSend(const std::string& msg, int id) = 0;
    virtual ~IMessageCallback() = default;
};

template<typename Callback>
class Notification {
public:
    using CallbackWPtr = std::weak_ptr<Callback>;
    using CallbackPtr = std::shared_ptr<Callback>;
    using CallbackList = std::vector<CallbackWPtr>;

    void registerCallback(CallbackPtr callback) {
        std::scoped_lock lock(mMutex);

        if (findCallback(callback) == mCallbacks.cend()) {
            mCallbacks.emplace_back(callback);
        }
    }

    void unregisterCallback(CallbackPtr callback) {
        std::scoped_lock lock(mMutex);

        mCallbacks.erase(findCallback(callback));
    }

    template<typename Func, typename... Args>
    void notify(Func func, Args&&... args) {
        CallbackList liveCallbacks;
        liveCallbacks.reserve(mCallbacks.size());

        for (const auto& wcb : mCallbacks) {
            if (auto cb = wcb.lock()) {
                std::invoke(func, cb, std::forward<Args>(args)...);

                liveCallbacks.emplace_back(wcb);
            }
        }

        removeExpiredCallbacks(std::move(liveCallbacks));
    }

private:
    auto findCallback(CallbackPtr callback) {
        return std::find_if(mCallbacks.cbegin(), mCallbacks.cend(), [callback](auto& wcb) {
                if (auto cb = wcb.lock()) {
                    return cb == callback;
                } else {
                    return false;
                }
            });
    }

    /**
     * std::weak_ptr doesn't suppport compare operation, there's no way to get the 
     * iterator of a weak_ptr and then use erase to delete it from vector.
     * 
     * auto ite = std::remove_if(mCallbacks.begin(), mCallbacks.end(), [](const auto& wcb){
     *  return (auto cb = wcb.lock()) ? true : false;
     * });
     * mCallbacks.erase(ite, mCallbacks.end());
     */
    void removeExpiredCallbacks(CallbackList&& liveCallbacks) {
        std::scoped_lock lock(mMutex);

        if (liveCallbacks.size() < mCallbacks.size() / 3) {
            mCallbacks = liveCallbacks;
        }
    }

private:
    std::mutex mMutex;
    CallbackList mCallbacks; 
};

class MessageManager : public IMessageCallback {
public:
    void onDelete(const std::string& msg) override {
        std::cout << "ON delete callback msg: " << msg << std::endl;
    }

    void onSend(const std::string& msg, int id) override {
        std::cout << "ON Send callback msg: " << msg << ", id: " << id << std::endl;
    }
};

class Server : public Notification<IMessageCallback> {
public:
    Server() {
        mMsgManager = std::make_shared<MessageManager>();

        registerCallback(mMsgManager);
    }
    void deleteMessage(const std::string& msg)  {
        notify(&IMessageCallback::onDelete, msg);
    }

    void sendMessage(const std::string& msg, int id) {
        notify(&IMessageCallback::onSend, "msg", id);
    }

private:
    std::shared_ptr<MessageManager> mMsgManager;
};

int main() {
    Server server;

    server.deleteMessage("You delted your message.");
    server.sendMessage("Alice sent a message to Bob", 1238);
}
