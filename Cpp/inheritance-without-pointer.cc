#include <any>
#include <iostream>

template<typename Interface>
class Implementation {
public:
    template<typename ConcreateType>
    Implementation(ConcreateType&& object)
    :   _Storage(std::forward<ConcreateType>(object)),
        _Getter([](std::any& storage) -> Interface& { return std::any_cast<ConcreateType&>(storage); })
    {}

    Interface* operator->() {
        return &_Getter(_Storage);
    }

private:
    std::any _Storage;
    Interface& (*_Getter)(std::any&);
};

class ICalculator {
public:
    virtual int calculate(int) const = 0;
    virtual ~ICalculator() = default;
};


class BigCalculator : public ICalculator {
public:
    int calculate(int data) const override {
        return data * 100;
    }
};

class SmallCalculator : public ICalculator {
public:
    int calculate(int data) const override {
        return data * 10;
    }
};

#define P(x) std::cout << x << std::endl;

int main() {
    using Calculator = Implementation<ICalculator>;

    auto bigCal = Calculator{BigCalculator()};
    auto smallCal = Calculator{SmallCalculator()};

    P("Big: " << bigCal->calculate(1));
    P("Small: " << smallCal->calculate(1));
}

// Refer: https://www.fluentcpp.com/2021/01/29/inheritance-without-pointers/