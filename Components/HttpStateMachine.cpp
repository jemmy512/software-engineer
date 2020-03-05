#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static std::vector<std::string> HttpHeaders{"GET", "POST"};

enum class LineState {
    Ok,
    Open,
    Bad
};

enum class ParseState {
    RequestLine,
    Header
};

enum class HttpState {
    NoRequest,
    GetRequest,
    BadRequest,
    InternalError,
    CloseConnection
};

LineState parseLine(char* buf, int& parsePos, const int& endPos) {
    int initPos = parsePos;
    for (; parsePos < endPos; ++parsePos) {
        char tmp = buf[parsePos];
        if (tmp == '\r') {
            if (parsePos + 1 == endPos) {
                return LineState::Open;
            } else if (buf[parsePos+1] == '\n') {
                buf[parsePos++] = '\0';
                buf[parsePos++] = '\0';
                return LineState::Ok;
            } else {
                return LineState::Bad;
            }
        } else if (tmp == '\n') {
            if (parsePos > 1 && buf[parsePos-1] == '\r') {
                buf[parsePos-1] = '\0';
                buf[parsePos++] = '\0';
                return LineState::Ok;
            } else {
                return LineState::Bad;
            }
        }
    }

    return LineState::Open;
}

HttpState parseRequestLine(char* buf, ParseState& parseState) {
    char *url = strpbrk(buf, " ");
    if (!url) {
        return HttpState::BadRequest;
    } else {
        *url++ = '\0';
    }

    char* method = buf;
    if (strcasecmp(method, "GET") != 0
        && strcasecmp(method, "POST") != 0
        && strcasecmp(method, "DELETE") != 0) {

        return HttpState::BadRequest;
    }

    char* version = strpbrk(url, " ");
    if (!version) {
        return HttpState::BadRequest;
    } else {
        *version++ = '\0';
    }

    if (strcasecmp(version, "HTTP/1.1") != 0) {
        return HttpState::BadRequest;
    }

    printf("Get request lien: %s %s %s\n", method, url, version);

    parseState = ParseState::Header;
    return HttpState::NoRequest;


}

HttpState parseHeader(char *buf) {
    if (buf[0] == '\0') {
        return HttpState::GetRequest;
    } else {
        char *key = buf;
        char *value = strpbrk(buf, " ");
        if (!value) {
            return HttpState::BadRequest;
        } else {
           *value++ = '\0'; 
        }

        printf("Requet head: %s %s\n", key, value);

        return HttpState::NoRequest;
    }
}

HttpState parseContent(char* buf, int& parsePos, int& curLinepos, int& bufEndPos, ParseState& parseState) {
    LineState lineState = LineState::Open;
    HttpState httpState = HttpState::NoRequest;

    while ((lineState = parseLine(buf, parsePos, bufEndPos)) == LineState::Ok) {
        char* curLine = buf + curLinepos;
        curLinepos = parsePos;

        switch (parseState) {
            case ParseState::RequestLine: {
                httpState = parseRequestLine(curLine, parseState);
                if (httpState == HttpState::BadRequest) {
                    return HttpState::BadRequest;
                }

                break;
            }

            case ParseState::Header: {
                httpState = parseHeader(curLine);
                if (httpState == HttpState::BadRequest) {
                    return HttpState::BadRequest;
                } else if (httpState == HttpState::GetRequest) {
                    return HttpState::GetRequest;
                }

                break;
            }

            default:
                return HttpState::InternalError;
        }
    }

    return lineState == LineState::Open ? HttpState::NoRequest : HttpState::BadRequest;
}

int test() {
    char httpRequest[] = "GET /index.html HTTP/1.1\r\nHost: www.cisco.com\r\nKeep-Alive: Yes\r\nUser-Agent: WebexTeams\r\n\r\n";

    int parsePos = 0, curLinepos = 0, bufEndPos = strlen(httpRequest);
    ParseState parseState = ParseState::RequestLine;

    parseContent(httpRequest, parsePos, curLinepos, bufEndPos, parseState);

    return 0;
}

int main() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(9000);

    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenFd != -1);

    int on = 1;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    int ret = bind(listenFd, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(listenFd, 5);
    assert(ret != -1);

    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int connFd = accept(listenFd, (struct sockaddr*)&clientAddr, &clientLen);
    assert(connFd != -1);

    int parsePos = 0, curLinePos = 0, bufEndPos = 0, MaxLen = 4096;
    ParseState parseState = ParseState::RequestLine;
    char buf[MaxLen];

    const char* response200 = "Good Response\n";
    const char* response400 = "Bad Response\n";

    while (1) {
        int readLen = read(connFd, buf, MaxLen - bufEndPos);
        if (readLen <= 0) {
            printf("read error\n");
            break;
        } else {
            HttpState state = parseContent(buf, parsePos, curLinePos, bufEndPos, parseState);
            if (state == HttpState::GetRequest) {
                send(connFd, response200, sizeof(response200), 0);
                break;
            } else if (state == HttpState::NoRequest) {
                continue;
            } else {
                send(connFd, response400, sizeof(response400), 0);
                break;
            }
        }
    }

    close(connFd);
    close(listenFd);

    return 0;
}