#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>

#include <unistd.h> // close, shutdown
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/errno.h>
#include <chrono>

class Reactor;
Reactor gReactor;

class Reactor {
public:
    bool init(std::string&& ipAddr, short port = 9000, int threadNum = 5) {
        if (createListener(ipAddr, port) == false) {
            return false;
        }

        mAcceptThread = std::make_shared<std::thread>(acceptThreadRoutine, this);

        for (auto idx = 0; idx < threadNum; ++idx) {
            mWorkerThreads.emplace_back(std::make_shared<std::thread>(wokerThreadRountine, this));
        }

        return true;
    }

    bool uninit() {
        mIsRunning = false;

        mAcceptSingal.notify_all();
        mWorkSingal.notify_all();

        mAcceptThread->join();
        for (const auto& thread : mWorkerThreads) {
            thread->join();
        }
        
        ::epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mListenerFd, nullptr);

        ::shutdown(mListenerFd, SHUT_RDWR);
        ::close(mEpollFd);
        ::close(mListenerFd);
    }

    void run() {
        while (mIsRunning) {

        }
    }

public:
    static void exitHanlder(int signo) {
        std::cout << "Exit signal received: " << signo << std::endl;

        gReactor.uninit();
    }

private:
    void closeConnection(int fd) {
        ::epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, nullptr);

        ::close(fd);
    }

    void acceptThreadRoutine() {
        while (true) {

        }
    }

    void wokerThreadRountine() {
        while (true) {
            int activeFd = 0;

            {
                std::unique_lock<std::mutex> lock(mWorkerMutex);
                while (mListenedFd.empty) {
                    mWorkSingal.wait(lock);
                }

                if (!mIsRunning) {
                    return;
                }
                
                activeFd = mListenedFd.front();
                mListenedFd.pop();
            }

            std::string msg;
            char buffer[256];
            bool hasError = false;
            if (activeFd) {
                while (true) {
                    memset(&buffer, 0, 256);
                    auto len = ::recv(activeFd, buffer, 256, 0);
                    if (len == -1) {
                        if (errno == EWOULDBLOCK) {
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
                        if (errno == EWOULDBLOCK) {
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
                    
                    if (msg.empty) {
                        break;
                    }
                }
            }
        }
    }

    bool createListener(std::string& ipAddr, short port) {

    }

private:
    bool mIsRunning{true};
    int mEpollFd{-1};
    int mListenerFd{-1};

    std::shared_ptr<std::thread>    mAcceptThread;
    std::mutex                      mAcceptMutex;
    std::condition_variable         mAcceptSingal;

    std::vector<std::shared_ptr<std::thread>>   mWorkerThreads;
    std::mutex                                  mWorkerMutex;
    std::condition_variable                     mWorkSingal;

    std::queue<int> mListenedFd;
};

int main(int argc, char** argv) {
    signal(SIGCHLD, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, Reactor::exitHanlder);
	signal(SIGKILL, Reactor::exitHanlder);
	signal(SIGTERM, Reactor::exitHanlder);

    gReactor.init("0.0.0.0", 9000);

    gReactor.run();

    return 0;
}
