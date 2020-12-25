// This is example from
// http://vitiy.info/c11-functional-decomposition-easy-way-to-do-aop/
// by Victor Laskin

#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
using namespace std;


    #define LOG std::cout
    #define NL std::endl

    /// Simple immutable data
    class UserData {
    public:
        const int id;
        const string name;
        const int parent;
        UserData(int id, string name, int parent) : id(id), name(name), parent(parent) {}
    };

    /// Shared pointer to immutable data
    using User = std::shared_ptr<UserData>;

    /// Error type - code + description
    class Error {
    public:
        Error(int code, string message) : code(code), message(message) {}
        Error(const Error& e) : code(e.code), message(e.message) {}
        const int code;
        const string message;
    };


    /// MayBe monad from Haskel over shared_ptr
    /// with additional error field
    template < typename T >
    class Maybe {
    private:
        const T data;
        const shared_ptr<Error> error;
    public:
        Maybe(T data) : data(std::forward<T>(data)), error(nullptr) {}
        Maybe() : data(nullptr), error(nullptr) {}
        Maybe(decltype(nullptr) nothing) : data(nullptr), error(nullptr) {}
        Maybe(Error&& error) : data(nullptr), error(make_shared<Error>(error)) {}

        bool isEmpty() { return (data == nullptr); };
        bool hasError() { return (error != nullptr); };
        T operator()(){ return data; };
        shared_ptr<Error> getError(){ return error; };

    };

    template <class T>
    Maybe<T> just(T t)
    {
        return Maybe<T>(t);
    }

    // Helpers to convert lambda into std::function

    template <typename Function>
    struct function_traits
    : public function_traits<decltype(&Function::operator())>
    {};

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const>
    {
        typedef ReturnType (*pointer)(Args...);
        typedef std::function<ReturnType(Args...)> function;
    };

    template <typename Function>
    typename function_traits<Function>::function
    to_function (Function& lambda)
    {
        return static_cast<typename function_traits<Function>::function>(lambda);
    }


    // Aspect logging duration of execution
    template <typename R, typename ...Args>
    std::function<R(Args...)> logged(string name, std::function<R(Args...)> f)
    {
        return [f,name](Args... args){

            LOG << name << " start" << NL;
            auto start = std::chrono::high_resolution_clock::now();

            R result = f(std::forward<Args>(args)...);

            auto end = std::chrono::high_resolution_clock::now();
            auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            LOG << "Elapsed: " << total << "us" << NL;

            return result;
        };
    }

    // Security checking
    template <typename R, typename ...Args, typename S>
    std::function<Maybe<R>(Args...)> secured(S session, std::function<Maybe<R>(Args...)> f)
    {
        // if user is not valid - return nothing
        return [f, &session](Args... args) -> Maybe<R> {
            if (session.isValid())
                return f(std::forward<Args>(args)...);
            else
                return Error(403, "Forbidden");
        };
    }


    // Use local cache (memoize)
    template <typename R, typename C, typename ...Args>
    std::function<Maybe<R>(Args...)> cached(C & cache, std::function<Maybe<R>(Args...)> f)
    {
        return [f,&cache](Args... args){

            // get key as tuple of arguments
            auto key = make_tuple(args...);

            if (cache.count(key) > 0)
                return just(cache[key]);
            else
            {
                Maybe<R> result = f(std::forward<Args>(args)...);
                if (!result.hasError())
                    cache.insert(std::pair<decltype(key), R>(key, result())); //add to cache
                return result;
            }
        };
    }

    // If there was error - try again
    template <typename R, typename ...Args>
    std::function<Maybe<R>(Args...)> triesTwice(std::function<Maybe<R>(Args...)> f)
    {
        return [f](Args... args){
            Maybe<R> result = f(std::forward<Args>(args)...);
            if (result.hasError())
                return f(std::forward<Args>(args)...);
            return result;
        };
    }

    // Treat empty state as error
    template <typename R, typename ...Args>
    std::function<Maybe<R>(Args...)> notEmpty(std::function<Maybe<R>(Args...)> f)
    {
        return [f](Args... args) -> Maybe<R> {
            Maybe<R> result = f(std::forward<Args>(args)...);
            if ((!result.hasError()) && (result.isEmpty()))
                return Error(404, "Not Found");
            return result;
        };
    }

    template <typename R, typename ...Args>
    std::function<R(Args...)> locked(std::mutex& m, std::function<R(Args...)> f)
    {
        return [f,&m](Args... args){
            std::unique_lock<std::mutex> lock(m);
            return f(std::forward<Args>(args)...);
        };
    }

    // Couple of additional helpers

    template <class F, class... Args>
    void for_each_argument(F f, Args&&... args) {
        (void)(int[]){(f(forward<Args>(args)), 0)...};
    }

    template <class T, class... P>
    inline auto make(P&&... args) -> T {
        return std::make_shared<typename T::element_type>(std::forward<P>(args)...);
    }


int main() {

	// Database...
	vector<User> users {make<User>(1, "John", 0), make<User>(2, "Bob", 1), make<User>(3, "Max", 1)};

	// Request method
        auto findUser = [&users](int id) -> Maybe<User> {
            for (User user : users) {
                if (user->id == id)
                    return user;
            }
            return nullptr;
        };

        // Local cache
        map<tuple<int>,User> userCache;

        // Security
        class Session {
        public:
            bool isValid() { return true; }
        } session;

        // Mutex to test locked aspect
        std::mutex lockMutex;

        // Main functional factorization
        auto findUserFinal = locked(lockMutex, secured(session, notEmpty( cached(userCache, triesTwice( logged("findUser", to_function(findUser)))))));

		// TEST:

		auto testUser = [&](int id) {
            auto user = findUserFinal(id);
            LOG << (user.hasError() ? "ERROR: " + user.getError()->message : "NAME:" + user()->name) << NL;
        };

        for_each_argument(testUser, 2, 30, 2, 1);

	return 0;
}
