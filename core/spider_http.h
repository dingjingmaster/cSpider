/*************************************************************************
> FileName: spider_http.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 15时21分23秒
 ************************************************************************/
#ifndef _SPIDER_HTTP_H
#define _SPIDER_HTTP_H
#include <iostream>

using namespace std;

#define HTTP_GET_RECEIVE_BUFFER_SIZE 409600
typedef struct _requestHttpInfo RequestHttpInfo;
typedef struct _replyHttpInfo ReplyHttpInfo;

struct _requestHttpInfo {
    string type;                                                    //  请求类型是 http 还是 https
    string ip;                                                      //  ip
    string port;                                                    //  端口
    string request;                                                 //  请求的数据
};

struct _replyHttpInfo {
    unsigned int status;                                            //  状态信息
    std::string pageInfo;                                           //  html 消息体
};


class SpiderHttp {
public:
    SpiderHttp();
    ~SpiderHttp();
    void setUrl(string& url);


    void http_get_start();
    const char* http_get_html();
    string http_get_ip();
    string http_get_request();
    void http_get_parse(char* recvBuf); 
    void http_parse_url();
    void http_get(char* recvBuf, size_t len); 

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
};
#endif
