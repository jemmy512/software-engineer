#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <future>

#include "lockable.cc"

template<typename Signature>
class CallbackRepository;

template<typename R, typename... Args>
class CallbackRepository<R(Args...)> {
public:
    using CallbackType = std::function<void(Args...)>;

    struct Entry {
        Entry(const CallbackType& callback)
        :   _IsOwner(false),
            _WeakThis(),
            _Callback([callback](const std::shared_ptr<void>&, Args... args) {
                callback(args...);
            })
        {}

        Entry(const std::shared_ptr<void>& sharedThis, const CallbackType& callback)
        :   _IsOwner(true),
            _WeakThis(sharedThis),
            _Callback([callback](const std::shared_ptr<void>&, Args... args) {
                callback(args...);
            })
        {}

        Entry(const std::shared_ptr<void>& sharedThis, const std::function<void(const std::shared_ptr<void>&, Args...)>& callback)
        :   _IsOwner(true),
            _WeakThis(sharedThis),
            _Callback(callback)
        {}

        bool isExpired() const {
            return _IsOwner && _WeakThis.expired();
        }

        bool _IsOwner;
        std::weak_ptr<void> _WeakThis;
        std::function<void(const std::shared_ptr<void>&, Args...)> _Callback;
    };

    template<typename T>
    Entry entryFromLambda(std::shared_ptr<T&> sharedThis, std::function<void(Args...)>& lambda) {
        return Entry(sharedThis, [lambda](std::shared_ptr<void>& sharedThis, Args... args) {
            if (sharedThis) {
                lambda(args...);
            }
        });
    }

    template<typename T>
    Entry entryFromMemberFunction(std::shared_ptr<T>& sharedThis, void(T::*memFn)(Args...)) {
        return Entry(sharedThis, [memFn](const std::shared_ptr<void>& shared, Args... args) {
            // if (auto sharedThis = *(std::shared_ptr<T>*)(&shared)) {
            if (auto sharedThis = *reinterpret_cast<const std::shared_ptr<T>*>(&shared)) {
                ((*sharedThis).*memFn)(args...);
            }
        });
    }


public:
    void operator()(Args... args) {
        if (auto entries = _Entries.lock()) {
            for (auto& weak : getEntries()) {
                weak._Callback(weak._WeakThis.lock(), args...);
            }
        }
    }

    // void addEntry(const CallbackType& entry) {
    //     if (auto lockedEntries = _Entries.lock()) {
    //         lockedEntries->emplace_back(Entry(entry));
    //     }
    // }

    void addEntry(const Entry& entry) {
        if (auto lockedEntries = _Entries.lock()) {
            lockedEntries->emplace_back(entry);
        }
    }

    std::vector<Entry> getEntries() {
        std::vector<Entry> result;

        if (auto lockedEntries = _Entries.lock()) {
            auto idx = 0;
            for (auto iter = lockedEntries->begin(); iter != lockedEntries->end();) {
                if (iter->isExpired()) {
                    iter = lockedEntries->erase(iter);
                } else {
                    result.emplace_back(*iter);
                    ++iter;
                }
            }
        }

        return result;
    }

private:
    Lockable<std::vector<Entry>> _Entries;
};


struct Contact {
    void nameAge(int age, std::string name) {
        std::cout << name << "' age is " << age << std::endl;
    }
};

int main() {
    CallbackRepository<void(int, std::string)> callbacks;

    /** Implicit construction supports constructor only with one parameter,
     * initializer_list can support constructor with variadic parameters. */

    // callbacks.addEntry([](int age, std::string name) {
    //     std::cout << "Age: " + std::to_string(age) + ", Name: " << name << std::endl;
    // });

    callbacks.addEntry({[](int age, std::string name) {
        std::cout << "Age: " + std::to_string(age) + ", Name: " << name << std::endl;
    }});

    callbacks.addEntry({[](int number, std::string name) {
        std::cout << "number: " + std::to_string(number) + ", Name: " << name << std::endl;
    }});

    callbacks.addEntry(callbacks.entryFromMemberFunction(std::make_shared<Contact>(), &Contact::nameAge));

    auto futureA = std::async(std::launch::async, [&callbacks]() {
        callbacks(0, "Future A");
    });

    auto futureB = std::async([&callbacks]() {
        callbacks(1, "Future B");
    });

    std::thread threadA([&callbacks]() {
        callbacks(22, "Li");
    });

    std::thread threadB([&callbacks]() {
        callbacks(12, "Jie");
    });

    futureA.wait();
    futureB.wait();

    threadA.join();
    threadB.join();

    return 0;
}