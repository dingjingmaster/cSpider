/*************************************************************************
	> File Name: spider_http.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 13时09分55秒
 ************************************************************************/

#ifndef _SPIDER_HTTP_HPP
#define _SPIDER_HTTP_HPP
#include <iostream>
#include <string>
#include <cstdlib>

namespace CSpider {
namespace Http {
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
        SpiderHttp() {
            requestHttpInfo = new RequestHttpInfo;
            replyHttpInfo = new ReplyHttpInfo;
        }

        


    /*  属性开始  */
    private:
        const std::string accept;
        const std::string acceptCharset;
        const std::string acceptEncoding;
        const std::string acceptLanguage;
        const std::string connection;
        const std::string cookie;
        const std::string userAgent;

        std::string host;

        RequestHttpInfo*  requestHttpInfo;
        ReplyHttpInfo*    replyHttpInfo;
    }


}
}

#endif
