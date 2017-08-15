/*************************************************************************
	> File Name: spider_http.h
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 13时09分55秒
 ************************************************************************/

#ifndef SPIDER_HTTP_H
#define SPIDER_HTTP_H
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
        SpiderHttp(const std::string& host);

        // 执行 http get请求并返回结果
        void http_get_start();
        const char* http_get_html();


    protected:
        void http_get_parse(char* recvBuf); 

        void http_parse_url(); 
        void http_get(char* recvBuf, size_t len); 


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
}}

#endif
