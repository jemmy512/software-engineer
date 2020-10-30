#include <vector>
#include <functional>
#include <iostream>

#include "../Components/Lockable.cc"

template <typename Signature>
class Delegate;

template <typename R, typename... Args>
class Delegate<R(Args...)>
{
public:
    using Callback = std::function<void(Args...)>;

    struct Entry
    {
        Entry(const Callback& _callback)
        :   weak(),
            hasPointer(false),
            callback([_callback](const std::shared_ptr<void>&, Args... args) { _callback(args...); })
        {}

        Entry(const std::shared_ptr<void>& shared, const Callback& _callback)
        :   weak(shared),
            hasPointer(true),
            callback([_callback](const std::shared_ptr<void>&, Args... args) { _callback(args...); })
        {}

        Entry(const std::shared_ptr<void>& shared, const std::function<void(const std::shared_ptr<void>&, Args...)>& _callback)
        :   weak(shared),
            hasPointer(true),
            callback(_callback)
        {}

        Entry(const Entry& entry)
        :   weak(entry.weak),
            hasPointer(entry.hasPointer),
            callback(entry.callback)
        {}

        bool isExpired() {
            return hasPointer && weak.expired();
        }

        bool hasPointer;
        std::weak_ptr<void> weak;
        std::function<void(const std::shared_ptr<void>&, Args...)> callback;
    };

    void addEntry(const Entry& entry) {
        if (auto entries = mEntries.lock()) {
            entries->emplace_back(entry);
        }
    }

public:
    Delegate() = default;
    ~Delegate() = default;

    void clear() {
        if (auto entries = mEntries.lock()) {
            entries->clear();
        }
    }

    void operator()(Args... args) const {
        for (auto& entry : getEntries()) {
            entry.callback(entry.weak.lock(), args...);
        }
    }

    Delegate& operator+=(const Callback& callback) {
        addEntry(Entry(callback));
        return *this;
    }

    explicit operator bool() const {
        return !getEntries().empty();
    }

    template <typename T>
    static Entry entry_from_member_function(const std::shared_ptr<T>& shared, void (T::*memFn)(Args...)) {
        return Entry(shared, [memFn](const std::shared_ptr<void>& _shared, Args... args) {
            // if (auto sharedThis = *(const std::shared_ptr<T>*)(&_shared)) {
            if (auto sharedThis = std::static_pointer_cast<T>(_shared)) {
                ((*sharedThis).*memFn)(args...);
            }
        });
    };

    template <typename T>
    static Entry entry_from_lambda(const std::shared_ptr<T>& shared, const std::function<void(Args...)>& lambda) {
        return Entry(shared, [lambda](const std::shared_ptr<void>& _shared, Args... args) {
            if (_shared)
                lambda(args...);
        });
    }

    template <typename T>
    static Entry entry_from_lambda(
        const std::shared_ptr<T>& shared,
        const std::function<void(const std::shared_ptr<T>& shared, Args...)>& lambda) {

        return Entry(shared, [lambda](const std::shared_ptr<void>& _shared, Args... args) {
            if (auto sharedThis = *(const std::shared_ptr<T>*)(&_shared)) {
                lambda(sharedThis, args...);
            }
        });
    }

    template <typename T>
    struct callback_builder
    {
        callback_builder(Delegate& _delegate, const std::shared_ptr<T>& _shared)
        : delegate(_delegate), shared(_shared) { }

        void operator,(void (T::*memFn)(Args...)) {
            delegate.addEntry(Delegate::entry_from_member_function<T>(shared, memFn));
        }

        void operator,(const std::function<void(Args...)>& lambda) {
            delegate.addEntry(Delegate::entry_from_lambda<T>(shared, lambda));
        }

        std::shared_ptr<T> shared;
        Delegate& delegate;
    };

    template <typename T>
    callback_builder<T> operator+=(T* instance) {
        return callback_builder<T>(*this, std::dynamic_pointer_cast<T>(instance->shared_from_this()));
    }

    template <typename T>
    callback_builder<T> operator+=(const std::shared_ptr<T>& shared) {
        return callback_builder<T>(*this, shared);
    }

protected:
    mutable Lockable<std::vector<Entry>> mEntries;

    std::vector<Entry> getEntries() const
    {
        std::vector<Entry> validEntries;

        // this logic below does a lazzy clean-up of expired entries
        if (auto entries = mEntries.lock()) {
            for (auto it = entries->begin(); it != entries->end();) {
                if (it->isExpired()) {
                    it = entries->erase(it);
                } else {
                    validEntries.emplace_back(*it);
                    it++;
                }
            }
        }

        return validEntries;
    }
};

class Manager {
public:
    void foo() {
        std::cout << "Foo" << std::endl;
    }
};

int main() {
    Delegate<void()> myDelegate;
    auto manager = std::make_shared<Manager>();

    myDelegate += manager, &Manager::foo;
    myDelegate += []() { std::cout << "Lambda" << std::endl; };

    myDelegate();

    return 0;
}

/* Delegation is a way to make composition as powerful for reuse as inheritance [Lie86, JZ91].
 * In delegation, two objects are involved in handling a request: a receiving object delegates operations
 * to its delegate. This is analogous to subclasses deferring requests to parent classes.
 * But with inheritance, an inherited operation can always refer to the receiving object through the
 * this member variable in C++ and self in Smalltalk. To achieve the same effect with delegation,
 * the receiver passes itself to the delegate to let the delegated operation refer to the receiver. */