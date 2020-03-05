#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <thread>

#include <chrono>
#include <ctime>
#include <iomanip>

class IThreadPool;

namespace TimeUtil {
    std::string getCurrentTime() {
        auto timePoint = std::chrono::system_clock::now();
        auto timeT = std::chrono::system_clock::to_time_t(timePoint);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }
}

class Logger {
public:
    using Ptr = std::shared_ptr<Logger>;

    virtual void logMessage(const std::string&) = 0;
    virtual void finalize() = 0;
    virtual ~Logger() = default;
};

enum class LogLevel {
    INFO,
    ERROR,
    DEBUG
};

struct LogInfo {
    const LogLevel& level;
    const std::string& msg;
    const std::string& file;
    int line;
    const std::string function;
};


class LoggerManager {
public:
    static LoggerManager& instance();
    void logMessage(LogInfo&& logInfo);

    void registerLogger(const Logger::Ptr& logger);
    void unregisterLogger(const Logger::Ptr& logger);

private:
    std::string level2String(const LogLevel&);
    void filterString(std::string& msg, const std::vector<std::string>&& pii);


private:
    std::vector<Logger::Ptr> mLoggers;
    std::shared_ptr<IThreadPool> mThreadPool;
    std::vector<std::string> mPII;


    static constexpr auto PII_INFO = "********";
};

std::string LoggerManager::level2String(const LogLevel& level) {
    switch (level) {
        case LogLevel::INFO:  return "INFO";  break;
        case LogLevel::ERROR: return "ERROR"; break;
        case LogLevel::DEBUG: return "DEBUG"; break;
        default:    return "";
    }
}

void LoggerManager::filterString(std::string& msg, const std::vector<std::string>&& pii) {
    for (const auto& item : pii) {
        auto ite = msg.find(item);
        while (ite != std::string::npos) {
            msg.erase(ite, item.size());
            msg.insert(ite, PII_INFO);
            ite = msg.find(item, ite);
        }
    }
}

LoggerManager& LoggerManager::instance() {
    static LoggerManager instance;

    return instance;
}

void LoggerManager::logMessage(LogInfo&& logInfo) {
    std::stringstream ss;
    ss << TimeUtil::getCurrentTime() << " <" << level2String(logInfo.level) << ">" << " [" << std::this_thread::get_id() << "] " << logInfo.file << ":" << logInfo.function << " : " << logInfo.msg;
    auto formatedMessage = ss.str();
    for (const auto& logger : mLoggers) {
        logger->logMessage(formatedMessage);
    }
}

void LoggerManager::registerLogger(const Logger::Ptr& logger) {
    if (std::find(mLoggers.begin(), mLoggers.end(), logger) == mLoggers.end()) {
        mLoggers.emplace_back(logger);
    }
}

void LoggerManager::unregisterLogger(const Logger::Ptr& logger) {
    auto iter = std::find(mLoggers.begin(), mLoggers.end(), logger); 
    if (iter != mLoggers.end()) {
        logger->finalize();
        mLoggers.erase(iter);
    }
}

#define LogMessage(level, msg) \
{\
    std::ostringstream oss;\
    oss << msg;\
    LoggerManager::instance().logMessage({LogLevel:: level, oss.str(), __FILE__, __LINE__, __FUNCTION__});\
}

#define Info(msg)   LogMessage(INFO, msg);
#define Error(msg)  LogMessage(ERROR, msg);
#define Debug(msg)  LogMessage(DEBUG, msg);


class FileLogger : public Logger {
public:
    void logMessage(const std::string&) override;
    void finalize() override {}
};

class DatawareHouseLogger : public Logger {
public:
    void logMessage(const std::string&) override;
    void finalize() override {}
};

void FileLogger::logMessage(const std::string& message) {
    std::cout << "Filer Logger: " << message << std::endl;
}

void DatawareHouseLogger::logMessage(const std::string& message) {
    std::cout << "Dataware House Logger: " << message << std::endl;
}


int main() {
    std::shared_ptr<Logger> fileLogger = std::dynamic_pointer_cast<Logger>(std::make_shared<FileLogger>());
    std::shared_ptr<Logger> dbLogger = std::dynamic_pointer_cast<Logger>(std::make_shared<DatawareHouseLogger>());

    LoggerManager::instance().registerLogger(fileLogger);
    LoggerManager::instance().registerLogger(dbLogger);

    Info("information");

    Error(404);

    Debug("--- debug info --- " << "it's ok.");

    return 0;
}