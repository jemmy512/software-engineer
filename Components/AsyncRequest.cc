#include "./FunctionUtil.h"

#include <functional>
#include <iostream>
#include <string>

template <typename... Callbacks>
struct Request
{
    using ActionDelegate = std::function<void(Callbacks...)>;

    ActionDelegate action;

    Request() = default;

    Request(const ActionDelegate& action)
    :   action(action)
    { }

    Request(Request&& other)
    :   action(move(other.action))
    { }

    Request(const Request&) = delete;
    Request& operator=(const Request& other) = delete;
};

template <typename OnSuccess = std::function<void()>, typename OnError = std::function<void()>>
struct AsyncRequest : public Request<const OnSuccess&, const OnError&>
{
    using Request<const OnSuccess&, const OnError&>::Request; // inherit constructor

    OnSuccess successHandler;
    OnError errorHandler;

    AsyncRequest(AsyncRequest&& other)
    :   Request<const OnSuccess&, const OnError&>::Request(std::move(other)),
        errorHandler(std::move(other.errorHandler)),
        successHandler(std::move(other.successHandler))
    { }

    ~AsyncRequest() {
        if (this->action)
            this->action(successHandler, errorHandler);
    }

    AsyncRequest& onError(const OnError& errorHandler) {
        this->errorHandler = errorHandler;
        return *this;
    }

    template <typename T>
    AsyncRequest& onError(T* t, const OnError& errorHandler) {
        return onError(weak_handler(t, errorHandler));
    }

    AsyncRequest& onSuccess(const OnSuccess& successHandler) {
        this->successHandler = successHandler;
        return *this;
    }

    template <typename T>
    AsyncRequest& onSuccess(T* t, const OnSuccess& successHandler) {
        return onSuccess(weak_handler(t, successHandler));
    }

    template <typename Continuation,
        typename Arg0 = typename function_traits<Continuation>::template argument<0>,
        typename Arg1 = typename function_traits<Continuation>::template argument<1>>
    AsyncRequest<Arg0, Arg1> then(const Continuation& continuation) {
        return AsyncRequest<Arg0, Arg1>(
            [continuable = FunctionUtil::move(this->action), continuation, this]
            (const Arg0& onSuccess, const Arg1& onError) {
                continuable(function_traits<Continuation>::helper::rest_helper::bind(continuation, onSuccess, onError), errorHandler);
            }
        );
    }

    template <typename T,
        typename Continuation,
        typename Arg0 = typename function_traits<Continuation>::template argument<0>,
        typename Arg1 = typename function_traits<Continuation>::template argument<1>>
    AsyncRequest<Arg0, Arg1> then(T* t, const Continuation& continuation) {
        return then(weak_handler(t, continuation));
    }
};

int main() {
    using OnSuccess = std::function<void(std::string)>;
    using OnError = std::function<void(std::string)>;

    AsyncRequest<OnSuccess, OnError>([](OnSuccess suc, OnError err) {
        suc("success 0");
        err("error 0");
    }).onError([](std::string str) {
        std::cout << str << std::endl;
    }).then([](OnSuccess suc, OnError err, const std::string& str) {
        if (str.empty()) {

        } else {
            suc("success then");
            err("error then");
        }
    }).onSuccess([](const std::string& str) {
        std::cout << str << std::endl;
    }).onError([](std::string str) {
        std::cout << str << std::endl;
    });

    return 0;
}