#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <vector>

struct Process {
    pid_t mPid{-1};
    int mPipeFd[2];
};

int setNonBlock(int fd) {
    int oldFlag = fcntl(fd, F_GETFL);
    int newFlag = oldFlag | O_NONBLOCK;
    fcntl(fd, F_SETFL, newFlag);

    return oldFlag;
}

void epollAdd(int epollFd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
    setNonBlock(fd);
}

void epollRemove(int epollFd, int fd) {
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

void addsig(int sig, void(handler)(int), bool restart = true) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    if (restart) {
        sa.sa_flags |= SA_RESTART;
    }

    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, nullptr) != -1);
}

template<typename T>
class ProcessPool {
public:
    ProcessPool(int listenFd, int processNumber);
    ~ProcessPool();
    void run();

private:
    void init();
    void runChild();
    void runParent();

private:
    bool mIsRunning{ture};
    int mEpollFd{-1};
    int mListenFd{-1};
    int mProcessIndex{-1};
    int mProcessNumber{1};
    std::vector<Process> mSubProcess;

private:
    static const int MaxProcessNumber = 16;
    static const int MaxProcessCapability = 65535;
    static const int MaxEventNumber = 10000;

    static int mSigPipeFd[2];
    static void sigHandler(int);
};

template<typename T>
int ProcessPool<T>::mSigPipeFd[2] = {-1, -1};

template<typename T>
void ProcessPool<T>::sigHandler(int sig) {
    int oldErrno = errno;
    int msg = sig;
    send(mSigPipeFd[1], (char*)&msg, 1, 0);
    errno = oldErrno;
}

template<typename T>
~ProcessPool<T>::ProcessPool() {
    // close(mListenFd); // close by creator
    close(mEpollFd);
}

template<typename T>
void ProcessPool<T>::init() {
    mEpollFd = epoll_create(1);
    assert(mEpollFd != -1);

    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, mSigPipeFd);
    assert(ret != -1);

    setNonBlock(mSigPipeFd[1]);
    epollAdd(mEpollFd, mSigPipeFd[0]);

    addsig(SIGCHLD, sigHandler);
    addsig(SIGTERM, sigHandler);
    addsig(SIGINT, sigHandler);
    addsig(SIGPIPE, SIG_IGN);
}

template<typename T>
ProcessPool<T>::ProcessPool(int listenFd, int processNumber)
:   mListenFd(listenFd), mProcessNumber(processNumber) 
{
    assert(mProcessNumber > 0 && mProcessNumber < MaxProcessNumber);

    mSubProcess.reserve(mProcessNumber);
    for (int idx = 0; idx < mProcessNumber; ++idx) {
        mSubProcess.emplace_back(-1, -1, -1);
        int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, mSubProcess[idx].mPipeFd);
        assert(ret != -1);

        pid_t pid = fork();
        assert(pid >= 0);
        mSubProcess[idx].mPid = pid;
        if (pid > 0) {
            close(mSubProcess[idx].mPipeFd[1]);
        } else {
            close(mSubProcess[idx].mPipeFd[0]);
            mProcessIndex = idx;
            break;
        }
    }
}

template<typename T>
void ProcessPool<T>::run() {
    mProcessIndex == -1 ? runParent() : runChild();
}

template<typename T>
void ProcessPool<T>::runChild() {
    init();

    int pipeFd = mSubProcess[mProcessIndex].mPipeFd[1];
    epollAdd(mEpollFd, pipeFd);

    epoll_event events[MaxEventNumber];
    T userData[MaxProcessCapability];

    int num = 0;
    int ret = -1;

    while (mIsRunning) {
        num = epoll_wait(mEpollFd, events, MaxEventNumber, -1);
        if (num < 0 && errno != EINTR) {
            printf("epoll quit of error: %d\n", errno);
            break;
        }

        for (int i = 0; i < num; ++i) {
            int sockFd = events[i].data.fd;
            int event = events[i].events;

            if (sockFd == pipeFd && (event & EPOLLIN)) {
                int client;
                ret = recv(pipeFd, &client, sizeof(client), 0);
                if (ret == 0 || (ret < 0 && errno != EINTR)) {
                    continue;
                } else {
                    struct sockaddr_in clientAddr;
                    socklen_t clientLen = sizeof(clientAddr);
                    int connFd = accept(mListenFd, (struct sockaddr*)&clientAddr, &clientLen);
                    if (connFd < 0) {
                        printf("accept fialed, errno: %d\n", errno);
                        continue;
                    }
                    
                    epollAdd(mEpollFd, connFd);
                    // userData[connFd].init(mEpollFd, connFd, std::move(clientAddr));
                }
            } else if (sockFd == mSigPipeFd[0] && (event & EPOLLIN)) {
                int sig;
                char signals[1024];
                int ret = recv(mSigPipeFd[0], signals, sizeof(signals), 0);
                if (ret < 0) {
                    continue;
                }

                for (int i = 0; i < ret; ++i) {
                    switch(signals[i]) {
                        case SIGCHLD: {
                            pid_t pid;
                            int stat;
                            while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
                                continue;
                            }
                            break;
                        }
                        case SIGTERM:
                        case SIGINT: {
                            mIsRunning = false;
                            break;
                        }
                        default: 
                            break;
                    }
                }
            } else if (event | EPOLLIN) {
                // userData[sockFd].process();
            }
        }
    }

    // close(mListenFd); // close by craeator
    close(mEpollFd);
}

template<typename T>
void ProcessPool<T>::runParent() {
    init();

    epollAdd(mEpollFd, mListenFd);

    epoll_event events[MaxEventNumber];
    int roundRobin = 0;
    int newConn = 1;
    int num = 0;
    int ret = -1;

    while (mIsRunning) {
        num = epoll_wait(mEpollFd, events, MaxEventNumber, -1);
        if (num < 0 && (errno != EINTR)) {
            break;
        }

        for (int i = 0; i < num; ++i) {
            int sockFd = events[i].data.fd;
            int event = events[i].events;

            if (sockFd == mListenFd) {
                int idx = roundRobin;
                do {
                    if (mSubProcess[idx].mPid != -1) 
                        break;
                    idx = (idx+1)%mProcessNumber;
                } while (idx != roundRobin);

                if (mSubProcess[idx].mPid == -1) {
                    mIsRunning = false;
                    break;
                }

                roundRobin = (idx+1)%mProcessNumber;

                send(mSubProcess[idx].mPipeFd[0], &newConn, sizeof(newConn), 0);

            } else if (sockFd == mSigPipeFd[0] && event & EPOLLIN) {
                int sig;
                char signals[1024];
                
                num = recv(mSigPipeFd[0], &signals, sizeof(signals), 0);
                if (num <= 0) {
                    continue;
                } else {
                    for (int i = 0; i < num; ++i) {
                        switch(signals[i]) {
                            case SIGCHLD: {
                                pid_t pid;
                                int state;
                                bool exitAllChild = true;
                                while ((pid = waitpid(-1, &state, WNOHANG)) > 0) {
                                    for (int i = 0; i < mProcessNumber; ++i) {
                                        if (mSubProcess[i].mPid == pid) {
                                            printf("child[%d] join\n", pid);
                                            close(mSubProcess[i].mPipeFd[0]);
                                            mSubProcess[i].mPid = -1;
                                        }

                                        if (mSubProcess[i].mPid != -1) {
                                            exitAllChild = false;
                                        }
                                    }
                                }
                                
                                if (exitAllChild) {
                                    mIsRunning = false;
                                }

                                break;
                            }
                            case SIGTERM:
                            case SIGINT: {
                                printf("kill all child process\n");
                                for (int i = 0; i < mProcessNumber; ++i) {
                                    pid_t pid = mSubProcess[i].mPid;
                                    if (pid != -1) {
                                        kill(pid, SIGTERM);
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
}

int main() {

    return 0;
}