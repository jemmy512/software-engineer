#include "./FunctionTraits.h"

#include <iostream>
#include <memory>
#include <string>

template <typename Continuation>
struct Continuator
{
    using Action = std::function<void(const Continuation&)>;

    Action action;

    template <typename Lambda>
    Continuator(const Lambda& lambda)
    :   action(lambda)
    { }

    Continuator(const Action& action)
    :   action(action)
    { }

    ~Continuator() {
        if (action)
            action(nullptr);
    }

    operator Action() {
        return move(action);
    }

    template <typename Callable, typename Arg0 = typename function_traits<Callable>::template argument<0>>
    Continuator<Arg0> then(const Callable& callable) {
        return [continuable = FunctionTraits::move(action), callable](const Arg0& continuation) {
            continuable(function_traits<Callable>::helper::bind(callable, continuation));
        };
    }

    template <typename Callable, typename... Args>
    std::enable_if_t<is_continuable<Callable>::value, Continuator<typename function_traits<Callable>::template argument<0>>>
    then(const Callable& callable, Args... args) {
        return [continuable = FunctionTraits::move(action), callable, args...]
            (const typename function_traits<Callable>::template argument<0>& continuation) {
                continuable(function_traits<Callable>::helper::bind(callable, continuation));
            };
    }

    template <typename Lamdba>
    std::enable_if_t<!is_continuable<Lamdba>::value>
    then(const Lamdba& continuation) {
        if (auto continuable = FunctionTraits::move(action)) {
            continuable(continuation);
        }
    }
};

class Successor : std::enable_shared_from_this<Successor> {
public:
    void onSuccess(int i) {
        std::cout << "Successor: " << i << std::endl;
    }
};

int main() {
    using OnSuccess = std::function<void(int)>;
    using OnError = std::function<void(std::string)>;

    // std::function<void(int)>
    // std::function<void(const OnSuccess&)>
    Continuator<OnSuccess>([](OnSuccess suc){
        std::cout << "0" << std::endl;
        suc(1);
    }).then([](OnSuccess suc, int j) { // Arg: std::function<void(int)>
        std::cout << j << std::endl;
        suc(2);
    }).then([](OnError suc, int j) { // Arg: std::function<void(int)>
        std::cout << j << std::endl;
        suc("hi");
    }).then([](OnError suc, const std::string& str) { // Arg: std::function<void(std::string)>
        std::cout << str << std::endl;
    });
}

/*
[](argument<0>& continuation) {

    [](argument<0>& continuation) { // then 2

        [](argument<0>& continuation) { // then 1

            [](argument<0>& continuation) { // Continuator
                // logic 
                if (lambda1) {
                    lambda1(rest...);
                }

            }(bind(lambda1, continuation)); [](Rest... rest) -> continuator { lambda1(lambda2, rest...); }

        }(bind(lambda2, continuation)); []((Rest... rest)) -> continuator { lambda2(lambda3, rest...); }

    }(nullptr);

}(nullptr); */