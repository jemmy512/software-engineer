#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <cassert>

#define Pln(x) std::cout << x << std::endl;

int main(int argc, char** argv) {
    if (argc <= 3) {
        printf("Usage: ipAddress port fileName");
        return -1;
    }

    char* ipAddress = argv[1];
    int port = atoi(argv[2]);
    char* fileName = argv[3];

    Pln("ipAddress: " << ipAddress << ", port: " << port << ", fileName: " << fileName);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddress);
    address.sin_port = htons(port);

    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenFd >= 0);

    int on = 1;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    int ret = bind(listenFd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenFd, 5);
    assert(ret != -1);
    Pln("listen on port: " << port);

    struct sockaddr_in client;
    socklen_t clientLen = sizeof(client);
    int connFd = accept(listenFd, (struct sockaddr*)&client, &clientLen);
    assert(connFd >= 0);

    bool valid = false;
    char* responseBody{nullptr};
    struct stat fileStat;
    if (stat(fileName, &fileStat) != -1) {
        if (!S_ISDIR(fileStat.st_mode)) {
            if (fileStat.st_mode & S_IROTH) {
                int fileFd = open(fileName, O_RDONLY);
                
                responseBody = new char[fileStat.st_size + 1];
                if (read(fileFd, responseBody, fileStat.st_size) >= 0) {
                    valid = true;
                }
                
                close(fileFd);
            }
        }
    }

    std::string responseHeader;
    if (valid) {
        responseHeader += "HTTP/1.1 200 OK\r\n";
        responseHeader += "Content-Length: " + std::to_string(fileStat.st_size);
        responseHeader += "\r\n";

        struct iovec iov[2];
        iov[0].iov_base = responseHeader.data();
        iov[0].iov_len = responseHeader.size();
        iov[1].iov_base = responseBody;
        iov[1].iov_len = strlen(responseBody);

        writev(connFd, iov, 2);
    } else {
        responseHeader += "HTTP/1.1 500 Interner Server Error\r\n";
        responseHeader += "\r\n";

        send(connFd, responseHeader.data(), responseHeader.size(), 0);
    }

    if (responseBody)
    	delete[] responseBody;

    close(listenFd);


    return 0;
}