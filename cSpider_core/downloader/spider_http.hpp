/*************************************************************************
	> File Name: spider_http.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 13时09分55秒
 ************************************************************************/

#ifndef _SPIDER_HTTP_HPP
#define _SPIDER_HTTP_HPP
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>

namespace CSpider {
namespace Http {
    #define HTTP_GET_RECEIVE_BUFFER_SIZE 40960
    typedef struct _requestHttpInfo RequestHttpInfo;
    typedef struct _replyHttpInfo ReplyHttpInfo;

    struct _requestHttpInfo {
        std::string type;                             //  请求类型是 http 还是 https
        std::string ip;                               //  ip
        std::string port;                             //  端口
        std::string request;                          //  请求的数据
    };

    struct _replyHttpInfo {
        unsigned int status;                          //  状态信息
        std::string pageInfo;                         //  html 消息体
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

    protected:
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
            if(requestHttpInfo->http.empty()) {
                requestHttpInfo->http = "http";
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

        void http_get() {

            if(requestHttpInfo->ip.empty() || requestHttpInfo->port.empty() || requestHttpInfo.request.empty()) {

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
            ip = gethostbyname(requestHttpInfo->ip);
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
            memset(&servAddr, sizeof(servAddr));
            servAddr.sin_family = AF_INET;
            servAddr.sin_port = htons(port);
            servAddr.sin_addr = *((struct in_addr*)ip->h_addr);

            ret = connect(fd, (struct sockaddr*)(&servAddr), sizeof(struct sockaddr));
            if(-1 = ret) {
                
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

            send(fd, sendBuf.c_str(), sendBuf.length(), 0);

            char re[HTTP_GET_RECEIVE_BUFFER_SIZE] = {0};
            ret = recv(fd, re, HTTP_GET_RECEIVE_BUFFER_SIZE, 0);

            printf("%s\n", re);

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
    }


}
}

#endif
