#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <chrono>
#include <string>
#include <condition_variable>

#include <string.h>

#include <unistd.h> // close, shutdown
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/errno.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define Pln(x) std::cout << x << std::endl;

class Reactor {
private:
    bool mIsRunning{true};
    int mEpollFd{-1};
    int mListenerFd{-1};

    std::shared_ptr<std::thread>    mAcceptThread;
    std::mutex                      mAcceptMutex;
    std::condition_variable         mAcceptSignal;

    std::vector<std::shared_ptr<std::thread>>   mWorkerThreads;
    std::mutex                                  mWorkerMutex;
    std::condition_variable                     mWorkerSignal;

    std::queue<int> mActiveFds;

private:
    void closeConnection(int fd) {
        ::epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, nullptr);

        ::close(fd);

        Pln("?? Fd: " << fd << "closed");
    }

    void acceptThreadRoutine() {
        while (true) {
            int newFd;
            struct sockaddr_in addr;
            socklen_t len;
            {
                std::unique_lock<std::mutex> lock(mAcceptMutex);
                mAcceptSignal.wait(lock);

                if (!mIsRunning) {
                    Pln("AcceptThead exit...");
                    return;
                }

                newFd = ::accept4(mListenerFd, (sockaddr*)&addr, &len, SOCK_NONBLOCK);
            }
            
            if (newFd == -1)
                continue;

            struct epoll_event ev;
            ev.events = EPOLLIN | EPOLLRDHUP | EPOLLET;
            ev.data.fd = newFd;
            if (::epoll_ctl(mEpollFd, EPOLL_CTL_ADD, newFd, &ev) != -1) {
                Pln("** accept new Fd: " << newFd);
            }
        }
    }

    void workerThreadRountine() {
        while (true) {
            int activeFd = 0;
            {
                std::unique_lock<std::mutex> lock(mWorkerMutex);
                while (mActiveFds.empty()) {
                    if (!mIsRunning) {
                        Pln("^^^ Worker Thread [" << std::this_thread::get_id() << "] exit...");
                        return;
                    }

                    mWorkerSignal.wait(lock);
                }
                
                activeFd = mActiveFds.front();
                mActiveFds.pop();
            }

            std::string msg;
            char buffer[256];
            bool hasError = false;
            if (activeFd) {
                while (true) {
                    memset(&buffer, 0, 256);
                    auto len = ::recv(activeFd, buffer, 256, 0);
                    if (len == -1) {
                        if (errno == EWOULDBLOCK || errno == EINTR) {
                            break;
                        } else {
                            hasError = true;
                            closeConnection(activeFd);
                        }
                    } else if (len == 0) {
                        hasError = true;
                        closeConnection(activeFd);
                    }

                    msg += buffer;
                }

                if (hasError) {
                    continue;
                }

                auto time = std::chrono::steady_clock::now();
                while (true) {
                    auto len = ::send(activeFd, msg.c_str(), msg.length(), 0);
                    if (len == -1) {
                        if (errno == EWOULDBLOCK || errno == EINTR) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(10));
                            continue;
                        } else {
                            closeConnection(activeFd);
                            break;
                        }
                    } else if (len == 0) {
                        closeConnection(activeFd);
                        break;
                    }

                    msg.erase(0, len);
                    
                    if (msg.empty()) {
                        break;
                    }
                }
            }
        }
    }

    bool createListener(const std::string& ipAddr, short port) {
        mListenerFd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if (mListenerFd == -1)
            return false;

        int on = 1;
        ::setsockopt(mListenerFd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
        ::setsockopt(mListenerFd, SOL_SOCKET, SO_REUSEPORT, (char*)&on, sizeof(on));

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ipAddr.c_str());

        if (::bind(mListenerFd, (sockaddr*)&addr, sizeof(addr)) == -1)
            return false;

        if (::listen(mListenerFd, 50) == -1)
            return false;

        mEpollFd = ::epoll_create(1);
        if (mEpollFd == -1)
            return false;

        struct epoll_event ev;
        memset(&ev, 0, sizeof(ev));
        ev.events = EPOLLIN | EPOLLRDHUP;
        ev.data.fd = mListenerFd;
        if (::epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mListenerFd, &ev) == -1)
            return false;

        return true;
    }

public:
    bool init(std::string&& ipAddr, short port = 9000, int threadNum = 5) {
        if (!createListener(ipAddr, port)) {
            return false;
        }

        mAcceptThread = std::make_shared<std::thread>(&Reactor::acceptThreadRoutine, this);

        for (auto idx = 0; idx < threadNum; ++idx) {
            mWorkerThreads.emplace_back(std::make_shared<std::thread>(&Reactor::workerThreadRountine, this));
        }

        return true;
    }

    bool uninit() {
        mIsRunning = false;

        mAcceptSignal.notify_all();
        mWorkerSignal.notify_all();

        mAcceptThread->join();
        for (const auto& thread : mWorkerThreads) {
            thread->join();
        }
        
        ::epoll_ctl(mEpollFd, EPOLL_CTL_DEL, mListenerFd, nullptr);

        ::shutdown(mListenerFd, SHUT_RDWR);
        ::close(mListenerFd);
        ::close(mEpollFd);
    }

    void run() {
        while (mIsRunning) {
            struct epoll_event events[1024];
            int len = ::epoll_wait(mEpollFd, events, 1024, 10);
            if (len <= 0)
                continue;

            len = std::min(len, 1024);
            for (int idx = 0; idx < len; ++idx) {
                if (events[idx].data.fd == mListenerFd) {
                    mAcceptSignal.notify_one();
                } else {
                    std::unique_lock<std::mutex> lock(mWorkerMutex);
                    mActiveFds.push(events[idx].data.fd);
                    //mWorkerSignal.notify_one(); // better option?
                }
            }

            {
                std::unique_lock<std::mutex> lock(mWorkerMutex);
                if (!mActiveFds.empty())
                    mWorkerSignal.notify_all();
            }
        }

        Pln("event loop exit");
    }

public:
    static Reactor& instance() {
        static Reactor gReactor;
        return gReactor;
    }

    static void exitHanlder(int signo) {
        std::cout << "Exit signal received: " << signo << std::endl;

        Reactor::instance().uninit();
    }
};

void deamon() {
    pid_t childProcess = fork();
    if (childProcess <0) {
        Pln("Error: fork failed with errno: " << errno);
    } else if (childProcess >0) {
        Pln("INFO: forked child process: " << childProcess);
    }

    pid_t sessionId = setsid();
    Pln("INFO: New session id: " << sessionId);

    int fd = open("/dev/null", O_RDWR, 0);
    if (fd != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
    }

    if (fd > 2)
        close(fd);
}


int main(int argc, char** argv) {
    Pln("********* Main Thread start ************");

    signal(SIGCHLD, SIG_DFL);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, Reactor::exitHanlder);
    signal(SIGKILL, Reactor::exitHanlder);
    signal(SIGTERM, Reactor::exitHanlder);

    if (!Reactor::instance().init("0.0.0.0", 9000)) {
        Pln("exit by init error");
        return -1;
    }

    Reactor::instance().run();

    Pln("********* Main Thread exit ************");

    return 0;
}
