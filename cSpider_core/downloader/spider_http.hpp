/*************************************************************************
	> File Name: spider_http.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 13时09分55秒
 ************************************************************************/

#include <iostream>
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

namespace CSpider {
namespace Http {
    #define HTTP_GET_RECEIVE_BUFFER_SIZE 409600
    typedef struct _requestHttpInfo RequestHttpInfo;
    typedef struct _replyHttpInfo ReplyHttpInfo;

    struct _requestHttpInfo {
        std::string type;                                                 //  请求类型是 http 还是 https
        std::string ip;                                                   //  ip
        std::string port;                                                 //  端口
        std::string request;                                              //  请求的数据
    };

    struct _replyHttpInfo {
        unsigned int status;                                              //  状态信息
        std::string pageInfo;                                             //  html 消息体
    };

    /*  类开始  */
    class SpiderHttp {
        
    /*  构造与析构  */
    public:
        SpiderHttp(const std::string& host) : host(host) {
            requestHttpInfo = new RequestHttpInfo;
            replyHttpInfo = new ReplyHttpInfo;

            http_parse_url();
        }

        // 执行 http get请求并返回结果
        void http_get_start() {

            char*   pHead = NULL;
            char*   pEnd = NULL;
            char    recvBuf[HTTP_GET_RECEIVE_BUFFER_SIZE] = {0};          // 定义数据接收缓冲区

            // 解析 host
            http_parse_url();

            // 发送 get 请求
            http_get(recvBuf, HTTP_GET_RECEIVE_BUFFER_SIZE);

            // 解析出返回的 http 信息 
            http_get_parse(recvBuf);

            // 
            
            return;
        }



    protected:
        void http_get_parse(char* recvBuf) {

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
            std::cout << "|" << headBuf << "|" << std::endl;
            replyHttpInfo->status = atoi(headBuf);


            while (!(*(++pEnd) == '\n' && *(pEnd - 2) == '\n')) ;
            ++pEnd;                                                       // 之后是 html 开始

            // 找到<html> </html> 之间的信息
            pHead = pEnd;
            while(!(*(++ pEnd) == '<' && *(pEnd + 1) == 'h' && *(pEnd + 3) == 'm' && *(pEnd + 4) == 'l')); 
            memset(headBuf, 0, HTTP_GET_RECEIVE_BUFFER_SIZE);
            memcpy(headBuf, pEnd, HTTP_GET_RECEIVE_BUFFER_SIZE);

            replyHttpInfo->pageInfo = headBuf;

            return;

            //printf("%c%c%c%c%c%c\n", *pEnd, *(pEnd + 1), *(pEnd + 2), *(pEnd + 3), *(pEnd + 4), *(pEnd + 5));
            

            // 赋值

            //strncpy(headBuf, recvBuf, pEnd - pHead);

            //std::cout << headBuf << std::endl;
            //printf("%c%c%c%c%c\n", *(pEnd + 1), *(pEnd + 2), *(pEnd + 3), *(pEnd + 4), *(pEnd + 5));
        }
        void http_parse_url() {

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

        void http_get(char* recvBuf, size_t len) {

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

        


    /*  属性开始  */
    private:
        const std::string accept = "Accept: */*\r\n";
        const std::string userAgent = "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko\r\n";
        const std::string connection = "Connection: Keep-Alive\r\n";
        const std::string cookie;
        const std::string acceptCharset;
        const std::string acceptEncoding;
        const std::string acceptLanguage;

        std::string       host;

        RequestHttpInfo*  requestHttpInfo;
        ReplyHttpInfo*    replyHttpInfo;
    }; // 类结束
}
}

