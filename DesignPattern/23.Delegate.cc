#include <vector>
#include <functional>
#include <iostream>
#include <optional>

#include "../Components/Lockable.cc"

template <typename Signature>
class Delegator;

template <typename R, typename... Args>
class Delegator<R(Args...)>
{
public:
    using Callback = std::function<void(Args...)>;

    struct Entry
    {
        Entry(const Callback& _callback)
        :   weak(std::nullopt),
            callback([_callback](const std::shared_ptr<void>&, Args... args) { _callback(args...); })
        {}

        Entry(const std::shared_ptr<void>& shared, const Callback& _callback)
        :   weak(shared),
            callback([_callback](const std::shared_ptr<void>&, Args... args) { _callback(args...); })
        {}

        Entry(const std::shared_ptr<void>& shared, const std::function<void(const std::shared_ptr<void>&, Args...)>& _callback)
        :   weak(shared),
            callback(_callback)
        {}

        Entry(const Entry& entry)
        :   weak(entry.weak),
            callback(entry.callback)
        {}

        bool isExpired() {
            return weak && weak->expired();
        }

        std::optional<std::weak_ptr<void>> weak;
        std::function<void(const std::shared_ptr<void>&, Args...)> callback;
    };

    void addEntry(const Entry& entry) {
        if (auto entries = mEntries.lock()) {
            entries->emplace_back(entry);
        }
    }

public:
    Delegator() = default;
    ~Delegator() = default;

    void operator()(Args... args) const {
        for (auto& entry : getEntries()) {
            entry.callback(entry.weak->lock(), args...);
        }
    }

    Delegator& operator+=(const Callback& callback) {
        addEntry(Entry(callback));
        return *this;
    }

    explicit operator bool() const {
        if (auto entries = mEntries.lock()) {
            for (const auto& entry : entries) {
                if (!entry->isExpired()) {
                    return true;
                }
            }
        }

        return false;
    }

    void clear() {
        if (auto entries = mEntries.lock()) {
            entries->clear();
        }
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
        const std::function<void(const std::shared_ptr<T>& shared, Args...)>& lambda)
    {
        return Entry(shared, [lambda](const std::shared_ptr<void>& _shared, Args... args) {
            if (auto sharedThis = *(const std::shared_ptr<T>*)(&_shared)) {
                lambda(sharedThis, args...);
            }
        });
    }

    template <typename T>
    struct Builder
    {
        Builder(Delegator& _delegator, const std::shared_ptr<T>& _shared)
        : delegator(_delegator), shared(_shared) { }

        void operator,(void (T::*memFn)(Args...)) {
            delegator.addEntry(Delegator::entry_from_member_function<T>(shared, memFn));
        }

        void operator,(const std::function<void(Args...)>& lambda) {
            delegator.addEntry(Delegator::entry_from_lambda<T>(shared, lambda));
        }

        std::shared_ptr<T> shared;
        Delegator& delegator;
    };

    template <typename T>
    Builder<T> operator+=(T* instance) {
        return Builder<T>(*this, std::dynamic_pointer_cast<T>(instance->shared_from_this()));
    }

    template <typename T>
    Builder<T> operator+=(const std::shared_ptr<T>& shared) {
        return Builder<T>(*this, shared);
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
    Delegator<void()> myDelegator;
    auto manager = std::make_shared<Manager>();

    myDelegator += manager, &Manager::foo;
    myDelegator += []() { std::cout << "Lambda" << std::endl; };

    myDelegator();

    return 0;
}

/* Delegation is a way to make composition as powerful for reuse as inheritance [Lie86, JZ91].
 * In delegation, two objects are involved in handling a request: a receiving object delegates operations
 * to its delegator. This is analogous to subclasses deferring requests to parent classes.
 * But with inheritance, an inherited operation can always refer to the receiving object through the
 * this member variable in C++ and self in Smalltalk. To achieve the same effect with delegation,
 * the receiver passes itself to the delegator to let the delegated operation refer to the receiver. */