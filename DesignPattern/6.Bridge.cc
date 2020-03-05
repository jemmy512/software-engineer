#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <initializer_list>

#define Pln(x) std::cout << x << std::endl;

namespace TimeUtil {
    std::string getLocalTime() {
        auto now = std::chrono::system_clock::now();
        auto timeT = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }
}

class MsgSender {
public:
    virtual void send(const std::string& msg) = 0;
    virtual ~MsgSender() = default;
};

class EmailMsgSender : public MsgSender {
public:
    EmailMsgSender(std::initializer_list<std::string> emailAddresses)
    :   mEmailAddresses{emailAddresses}
    { }

    void send(const std::string& msg) override {
        Pln("[" << TimeUtil::getLocalTime() << "] sent email msg: " << msg);
    }
private:
    std::vector<std::string> mEmailAddresses;
};

class TelephoneMsgSender : public MsgSender {
public:
    TelephoneMsgSender(std::initializer_list<std::string> numbers)
    :   mTelephoneNumbers{numbers}
    { }

    void send(const std::string& msg) override {
        Pln("[" << TimeUtil::getLocalTime() << "] sent telephone msg: " << msg);
    }
    
private:
    std::vector<std::string> mTelephoneNumbers;
};

class ImMsgSender : public MsgSender {
public:
    ImMsgSender(std::initializer_list<std::string> ids)
    : mImIds{ids}
    { }

    void send(const std::string& msg) override {
        Pln("[" << TimeUtil::getLocalTime() << "] sent im msg: " << msg);
    }

private:
    std::vector<std::string> mImIds;
};


/*********************************************************************/


class Notification {
public:
    Notification(std::shared_ptr<MsgSender> msgSender)
    :   mMsgSender(msgSender)
    { }

    virtual void send(const std::string& msg) {
        mMsgSender->send(msg);
    }
protected:
    std::shared_ptr<MsgSender> mMsgSender;
};

class SevereNofitication : public Notification {
public:
    SevereNofitication(std::shared_ptr<MsgSender> telephoneMsgSender)
    :   Notification(telephoneMsgSender)
    { }
};

class UrgentNotification : public Notification {
public:
    UrgentNotification(std::shared_ptr<MsgSender> imMsgSender)
    : Notification(imMsgSender)
    { }
};

class NormalNotification : public Notification {
public:
    NormalNotification(std::shared_ptr<MsgSender> emailMsgSender)
    :   Notification(emailMsgSender)
    { }
};


int main() {
    ImMsgSender sender({"123", "456"});
    std::initializer_list<std::string> ids{"123", "456"};
    auto imSender = std::make_shared<ImMsgSender>(ids);

    std::initializer_list<std::string> numbers{"+86123", "+86456"};
    auto telephoneSender = std::make_shared<TelephoneMsgSender>(numbers);

    std::initializer_list<std::string> mails{"xxx@cisco.com", "xxx@cisco.com"};
    auto emailSender = std::make_shared<EmailMsgSender>(mails);


    auto severeNotificaiton = std::make_shared<SevereNofitication>(telephoneSender);
    auto urgentNotification = std::make_shared<UrgentNotification>(imSender);
    auto normalNotification = std::make_shared<NormalNotification>(emailSender);


    severeNotificaiton->send("[Severe] msg");
    urgentNotification->send("[Urgent] msg");
    normalNotification->send("[Normal] msg");

    return 0;
}

/**
 * Bridge:
 * Decouple the abstration from it's implement so the two can vary independently.
 */

/**
 * auto imSender = std::make_shared<ImMsgSender>({"123", "456"}); // compile error
 * 
 * The problem is that std::make_shared<T> is a partially specialized function template 
 * that can accept arguments of arbitrary number and type. Because of this, the compiler 
 * has no idea how to handle the initializer list.
 * 
 * A braced-init-list is never deduced as std::initializer_list<T> by template deduction.
 * 
 * https://stackoverflow.com/questions/24234480/stdmake-shared-with-stdinitializer-list
 * https://stackoverflow.com/questions/12431495/initializer-list-and-template-type-deduction
 */