#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using std::chrono::microseconds;

/* Proxy:
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
    UserControllerProxy(const UserControllerSP& ucSP) {
        userControllerSP = ucSP;
        metricsCollectorSP = std::make_shared<MetricsCollector>();
    }

    void login(const string& telephone, const string& password) override {
        auto startTimePoint = std::chrono::system_clock::now();

        userControllerSP->login(telephone, password);

        auto endTimePoint = std::chrono::system_clock::now();
        long responseTime = std::chrono::duration_cast<microseconds>(endTimePoint - startTimePoint).count();
        metricsCollectorSP->recordRequest("login", startTimePoint.time_since_epoch().count(), responseTime);
    }

    void signup(const string& telephone, const string& password) override {
        auto startTimePoint = std::chrono::system_clock::now();

        userControllerSP->signup(telephone, password);

        auto endTimePoint = std::chrono::system_clock::now();
        auto responseTime = std::chrono::duration_cast<microseconds>(endTimePoint - startTimePoint).count();
        metricsCollectorSP->recordRequest("register", startTimePoint.time_since_epoch().count(), responseTime);

    }
private:
    MetricsCollectorSP metricsCollectorSP;
    IUserControllerSP userControllerSP;
};

int main() {
    IUserControllerSP userController = std::make_shared<UserControllerProxy>(std::make_shared<UserController>());
    userController->login("jemmy", "hujk79");

    return 0;
}