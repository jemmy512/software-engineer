#include <iostream>
#include <vector>
#include <sstream>

class Logger  {
public:
    using Ptr = std::shard_ptr<Logger>;

    virtual void logMessage(const std::string&) = 0;
    virtual ~Logger() = defualt;
};


class LoggerManager {
public:
    enum Level {
        INFO,
        ERROR,
        DEBUG
    }

    static LoggerManger& instance();
    void logMessage(const Level& level, const std::string& msg, const std::string& file, int line, const std::string function);

    void registerLogger(const Logger::Ptr logger);
    void unregisterLogger(const Logger::Ptr logger);

private:
    std::string level2String(const Level&);
    void filterString(std::string& msg, const std::vector<std::string>& pii);


private:
    std::vector<Logger::Ptr> mLoggers;
    std::shared_ptr<IThreadPool> mThreadPool;
    std::vector<std::string> mPII;


    static constexpr auto PII_INFO = "********";
};

void LoggerManager::filterString(std::string& msg, cosnt std::vector<std::string>& pii) {
    for (const auto& item : pii) {
        auto ite = msg.find(item);
        while (ite != std::string::npos) {
            msg.erase(ite, item.size());
            msg.insert(ite, PII_INFO);
            ite = msg.find(item, ite);
        }
    }
}

std::string LoggerManagaer::level2String(const Level& level) {
    switch (level) {
        case INFO:  return "INFO";  break;
        case ERROR: return "ERROR"; break;
        case DEBUG: return "DEBUG"; break;
        default:    return "";
    }
}

LoggerManager& LoggerManager::instance() {
    static std::shared_ptr<LoggerManager> instance = std::make_shared<LoggerManager>();

    return instance;
}

void LoggerManager::logMessage(const Level& level, const std::string& msg, const std::string& file, int line, const std::string function) {
    std::stringstream ss;
    ss << "2020-2-10 14:23:45 " << "<" << level2String(level) << ">" << "[" << std::this_thread::get_id() << "] " << file << " : " << msg;
    auto formatedMessage = ss.str();
    for (const auto& logger : mLogger) {
        logger->logMessage(formatedMessage);
    }
}

void LoggerManager::registerLogger(const Logger::Ptr& logger) {
    if (std::find(mLoggers.begin(), mLogger.end(), logger) != mLogger.end()) {
        mLoggers.emplace_back(logger);
    }
}

void LoggerManager::unregisterLogger(const Logger::Ptr& logger) {
    auto iter = std::find(mLoggers.begin(), mLogger.end(), logger); 
    if (iter != mLogger.end()) {
        logger->fanalize();
        mLogger.erease(iter);
    }
}

#define LogMessage(level, msg) \
{\
    std::ostringstream oss;\
    oss << msg;\
    LoggerManager.instance().logMessage(LoggerManager::Lever:: level, oss.str(), __FILE__, __LINE__, __FUNCTION__);\
}

#define Info(msg)   LogMessage(INFO, msg);
#define Error(msg)  LogMessage(ERROR, msg);
#define Debug(msg)  LogMessage(DEBUG, msg);


class FileLogger : Logger {
public:
    void logMessage(const std::string&) override;
}

class DataWareHouseLogger : Logger {
public:
    void logMessage(const std::string&) override;
}

void FileLogger::logMessage(const std::string& messsage) {

}

void DatawareHouseLogger::logMessage(const std::string& message) {

}


int main() {

    return 0;
}