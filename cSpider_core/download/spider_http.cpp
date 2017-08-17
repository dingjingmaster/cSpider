/*************************************************************************
	> File Name: spider_http.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月15日 星期二 21时52分03秒
 ************************************************************************/

#include <spider_http.h>
using namespace CSpider::Http;

SpiderHttp::SpiderHttp(const std::string& host) {
    this->host = host;
    this->requestHttpInfo = new RequestHttpInfo;
    this->replyHttpInfo = new ReplyHttpInfo;
    http_parse_url();
}

// 执行 http get请求并返回结果
void SpiderHttp::http_get_start() {

    char*   pHead = NULL;
    char*   pEnd = NULL;
    char    recvBuf[HTTP_GET_RECEIVE_BUFFER_SIZE] = {0};          // 定义数据接收缓冲区
    // 智能指针管理缓冲区 尽量减少栈空间shiyong

    // 解析 host
    http_parse_url();

    // 发送 get 请求
    http_get(recvBuf, HTTP_GET_RECEIVE_BUFFER_SIZE);

    // 解析出返回的 http 信息 
    http_get_parse(recvBuf);

    // 
            
    return;
}

const char* SpiderHttp::http_get_html() {
    
    return replyHttpInfo->pageInfo.c_str();
}

std::string SpiderHttp::http_get_ip() {

    return requestHttpInfo->ip;
}

std::string SpiderHttp::http_get_request() {

    size_t  len = requestHttpInfo->request.length();
    std::string req = requestHttpInfo->request.substr(1, len - 1);

    return req;
}


void SpiderHttp::http_get_parse(char* recvBuf) {

    char*   pHead = recvBuf;
    char*   pEnd = recvBuf;
    char    headBuf[HTTP_GET_RECEIVE_BUFFER_SIZE] = {0};

    pHead = pEnd = recvBuf;

    // 获取返回状态码
    while(*(++ pEnd) != ' ');
    pHead = ++ pEnd;
    while(*(++ pEnd) != ' ');
    memset(headBuf, 0, HTTP_GET_RECEIVE_BUFFER_SIZE);
    strncpy(headBuf, pHead, pEnd - pHead);
    this->replyHttpInfo->status = atoi(headBuf);

    while (!(*(++pEnd) == '\n' && *(pEnd - 2) == '\n')) ;
        ++pEnd;                                                       // 之后是 html 开始

    // 找到<html> </html> 之间的信息
    pHead = pEnd;
    while(!(*(++ pEnd) == '<' && *(pEnd + 1) == 'h' && *(pEnd + 3) == 'm' && *(pEnd + 4) == 'l')); 
    memset(headBuf, 0, HTTP_GET_RECEIVE_BUFFER_SIZE);
    memcpy(headBuf, pEnd, HTTP_GET_RECEIVE_BUFFER_SIZE);

    replyHttpInfo->pageInfo = headBuf;

    return;
}

void SpiderHttp::http_parse_url() {

    if (host.empty()) {
    /////////
    }

    int startNum = 0;
    int endNum = 0;

    // type 
    endNum = host.find_first_of("//", startNum);
    if(endNum != std::string::npos) {
        endNum -= startNum;
        requestHttpInfo->type = host.substr (startNum, endNum - 1);
        startNum += endNum;
        startNum += 2;
    }

    // port
    endNum = host.find_first_of(":", startNum);
    if (endNum != std::string::npos) {
        endNum -= startNum;
        requestHttpInfo->ip = host.substr(startNum, endNum);
        startNum += endNum;
        ++ startNum;

        endNum = host.find_first_of("/", startNum);
        if(endNum != std::string::npos) {
            endNum == startNum;
            requestHttpInfo->port = host.substr(startNum, endNum);
            startNum += endNum;
            ++ startNum;
        } else {
            requestHttpInfo->port = host.substr(startNum, host.length());
            startNum = host.length();
        }
    } else {
        endNum = host.find_first_of("/", startNum);
        if(endNum != std::string::npos) {
            endNum -= startNum;
            requestHttpInfo->ip = host.substr(startNum, endNum);
            startNum += endNum;
            ++ startNum;
        } else {
            requestHttpInfo->ip = host.substr(startNum, host.length());
            startNum = host.length();
        }
    }

    // request
    if(startNum < host.length()) {
        requestHttpInfo->request = host.substr(startNum, host.length());
     }
            
    // 默认值
    if(requestHttpInfo->type.empty()) {
        requestHttpInfo->type = "http";
    }

    if(requestHttpInfo->port.empty()) {
        requestHttpInfo->port = "80";
    }

    if(requestHttpInfo->request.empty()) {
        requestHttpInfo->request = "/index.html";
    } else {
        requestHttpInfo->request = "/" + requestHttpInfo ->request;
    }

    return;
}

void SpiderHttp::http_get(char* recvBuf, size_t len) {

    if(requestHttpInfo->ip.empty() || requestHttpInfo->port.empty() || requestHttpInfo->request.empty()) {

        //////////
        return;
    }

    int                   fd;
    int                   ret;
    int                   port;
    std::string           sendBuf;
    std::string           receiveBuf;
    struct hostent*       ip;
    struct sockaddr_in    servAddr;

    // 获取 host 对应的 ip
    ip = gethostbyname(requestHttpInfo->ip.c_str());
    if(NULL == ip) {

        /////////
        return;
    }

    // 获取 端口
    port = atoi(requestHttpInfo->port.c_str());

    // socket 连接
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == fd) {
                
        ////////
        return;
    }

    // 连接
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr = *((struct in_addr*)ip->h_addr);

    ret = connect(fd, (struct sockaddr*)(&servAddr), sizeof(struct sockaddr));
    if(-1 == ret) {
                
        ///////
        return;
    }

    //
    sendBuf = "GET " + requestHttpInfo->request + " HTTP/1.1\r\n";
    sendBuf += "Host: " + requestHttpInfo->ip + "\r\n";
    sendBuf += SpiderHttp::accept;
    sendBuf += SpiderHttp::connection;
            
    if (!SpiderHttp::cookie.empty()) {
        sendBuf += SpiderHttp::cookie;
    }

    if (!SpiderHttp::acceptCharset.empty()) {
        sendBuf += SpiderHttp::acceptCharset;
    }

    if (!SpiderHttp::acceptEncoding.empty()) {
        sendBuf += SpiderHttp::acceptEncoding;
    }

    if (!SpiderHttp::acceptLanguage.empty()) {
        sendBuf += SpiderHttp::acceptLanguage;
    }

    sendBuf += "\r\n";

    ret = write(fd, sendBuf.c_str(), sendBuf.length());
    /////////////////

    sleep(1);
    ret = read(fd, recvBuf, len);
    if(0 >= ret) {
        //////////////////
        return;
    }

    close(fd);

    return;
}

        

