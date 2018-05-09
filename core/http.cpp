/*************************************************************************
> FileName: http.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月09日 星期三 14时44分36秒
 ************************************************************************/
#include "http.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

Http::Http () {
    body = new string;
}


Http::Http (Request& request) {
    body = new string;
    this->req = request;
}


Http::~Http () {
    delete body;
}


Http& Http::setRequest(Request& request) {
    this->req = request;

    return *this;
}


void Http::request() {
    int                     fd;
    int                     ret;
    int                     len = 0;
    char                    ip[512] = {0};
    char                    buf[819200] = {0};
    string                  receive;
    struct sockaddr_in      servAddr;
    Url                     url = req.getUrl();
    Request                 req = getRequest();

    // socket 连接
    fd = socket(url.getAddrType(), SOCK_STREAM, 0);
    if(-1 == fd) {
        //
    }

    ret = inet_pton(url.getAddrType(), url.getIp().c_str(), ip);

    // 连接
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = url.getAddrType();
    servAddr.sin_port = htons(80);
    servAddr.sin_addr = *((struct in_addr*)ip);

    ret = connect(fd, (struct sockaddr*)(&servAddr), sizeof(struct sockaddr));
    if(-1 == ret) {
        cout << "error" << endl;
        return;
    }

    //cout << req.get() << endl;

    memset(buf, 0, sizeof(buf));
    ret = write(fd, req.get().c_str(), req.get().length());
    usleep(300000);
    ret = read(fd, buf, sizeof(buf));
    if(0 >= ret) {
        cout << "error" << endl;
        return;
    }

    cout << buf  << "|"<< endl;
    cout << receive << "|"<< endl;

    close(fd);
}

Request& Http::getRequest() {
    return this->req;
}



