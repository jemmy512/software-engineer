#include <iostream>
#include <string>
#include <stack>
#include <optional>

template<typename T>
class SnapshotItem {
public:
    SnapshotItem(const T& value) : mValue(value) { }

    T value() const {
        return mValue;
    }

private:
    T mValue;
};

template<typename T>
class ISnapshot {
public:
    using item_type = T;
    using snapshot_type = SnapshotItem<item_type>;
    using optional_type = std::optional<snapshot_type>;

    virtual snapshot_type createSnapShot() = 0;
    virtual void restoreSnapShot(const optional_type& snapshot) = 0;

    virtual ~ISnapshot() = default;
};

class InputText : public ISnapshot<int> {
public:
    void append(const std::string& str) {
        mText += str;
    }

    const std::string& getText() const {
        return mText;
    }

    snapshot_type createSnapShot() override {
        return snapshot_type(mText.size());
    }

    void restoreSnapShot(const optional_type& snapshot) override {
        if (snapshot) {
            mText = mText.substr(0, snapshot.value().value());
        }
    }

private:
    std::string mText;
};

template<typename T>
class SnapshotManager {
public:
    void push(const T& val) {
        mStack.emplace(val);
    }

    using optional_type = std::optional<T>;
    optional_type pop() {
        optional_type option;

        if (mStack.size()) {
            option.emplace(mStack.top());
            mStack.pop();
        }

        return option;
    }

private:
    std::stack<T> mStack;
};

int main() {
    InputText input;
    SnapshotManager<InputText::snapshot_type> manager;

    std::string str;
    while (std::cin >> str) {
        if (str == ":list") {
            std::cout << input.getText() << std::endl;
        } else if (str == ":undo") {
            input.restoreSnapShot(manager.pop());
        } else {
            manager.push(input.createSnapShot());
            input.append(str);
        }
    }

    return 0;
}

/**
 * Captures and externalizes an object’s internal state so that it can be restored later,
 * all without violating encapsulation. */