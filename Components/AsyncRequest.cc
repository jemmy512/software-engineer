#include <functional>

#include "./FunctionUtil.h"

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

    template <typename Continuation>
    AsyncRequest<typename function_traits<Continuation>::argument_0> then(const Continuation& continuation) {
        return std::move(
            AsyncRequest<typename function_traits<Continuation>::argument_0>(errorHandler,
                [continuable = move(this->action), continuation, errorHandler = this->errorHandler]
                (const typename function_traits<Continuation>::argument_0& onSuccess, const OnError& onError) {
                    continuable(function_traits<Continuation>::helper::rest_helper::bind(continuation, onSuccess, onError),errorHandler);
                }
            )
        );
    }

    template <typename T, typename Continuation>
    AsyncRequest<typename function_traits<Continuation>::argument_0> then(T* t, const Continuation& continuation) {
        return then(weak_handler(t, continuation));
    }
};