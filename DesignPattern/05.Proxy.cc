#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using std::chrono::microseconds;

/* Proxy: Provide a surrogate or placeholder for another object to control access to it.
 * 1. add functionalities without changing the original class,
 * 2. decouple the framework code with business code,
 * 3. the purpose is access control rather than enhancement.
 *
 * Use cases: RPC, Cache, Monitor, Authentication, Rate limit, Transaction, logging
 *
 * Implementation:
 * 1. implemnet same interface
 * 2. inheritance */

class IUserController {
public:
    virtual void login(const string& telephone, const string& password) = 0;
    virtual void signup(const string& telephone, const string& password) = 0;
    virtual ~IUserController() = default;
};
using IUserControllerSP = std::shared_ptr<IUserController>;

class UserController : public IUserController {
    void login(const string& telephone, const string& password) override {

    }

    void signup(const string& telephone, const string& password) override {

    }
};
using UserControllerSP = std::shared_ptr<UserController>;

class MetricsCollector {
public:
    void recordRequest(const string& name, long startTime, long responseTime) {
        std::cout << "Metric: [" << name << ", " << startTime << ", " << responseTime << "]" << std::endl;
    }
};
using MetricsCollectorSP = std::shared_ptr<MetricsCollector>;

class UserControllerProxy : public IUserController {
public:
    UserControllerProxy(const UserControllerSP& ucSP) 
    :   _UserControllerSP(ucSP), 
        _MetricsCollectorSP(std::make_shared<MetricsCollector>()) 
    {}

    void login(const string& telephone, const string& password) override {
        auto startTimePoint = std::chrono::system_clock::now();

        _UserControllerSP->login(telephone, password);

        auto endTimePoint = std::chrono::system_clock::now();
        long responseTime = std::chrono::duration_cast<microseconds>(endTimePoint - startTimePoint).count();
        _MetricsCollectorSP->recordRequest("login", startTimePoint.time_since_epoch().count(), responseTime);
    }

    void signup(const string& telephone, const string& password) override {
        auto startTimePoint = std::chrono::system_clock::now();

        _UserControllerSP->signup(telephone, password);

        auto endTimePoint = std::chrono::system_clock::now();
        auto responseTime = std::chrono::duration_cast<microseconds>(endTimePoint - startTimePoint).count();
        _MetricsCollectorSP->recordRequest("register", startTimePoint.time_since_epoch().count(), responseTime);

    }

private:
    const MetricsCollectorSP _MetricsCollectorSP;
    const IUserControllerSP _UserControllerSP;
};

int main() {
    IUserControllerSP userController = std::make_shared<UserControllerProxy>(std::make_shared<UserController>());
    userController->login("jemmy", "hujk79");

    return 0;
}