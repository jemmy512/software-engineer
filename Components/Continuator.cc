#include "./FunctionUtil.h"

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

    template <typename Callable, typename... Args>
    Continuator<typename function_traits<Callable>::argument_0> then(const Callable& callable, Args... args) {
        return [continuable = std::move(action), callable, args...] (const typename function_traits<Callable>::argument_0& continuation) {
            continuable(function_traits<Callable>::helper::bind(callable, continuation));
        };
    }
};