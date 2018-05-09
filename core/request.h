/*************************************************************************
> FileName: request.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月09日 星期三 08时50分09秒
 ************************************************************************/
#ifndef _REQUEST_H
#define _REQUEST_H
#include "url.h"
#include <iostream>

using namespace std;

class Request {
public:
    Request();
    Request(Url& url);
    ~Request();
    Request& setHttpVersion(string version);
    Request& setAccept(string accept);
    Request& setReferer(string referer);
    Request& setAcceptLanguage(string language);
    Request& setUserAgent(string agent);
    Request& setContentType(string content);
    Request& setHost(string host);
    Request& setContentLength(string contentLength);
    Request& setConnect(string connect);
    Request& setCache(string cache);
    Request& setCookies(string cookies);
    string& getHttpVersion();
    string& getAccept();
    string& getReferer();
    string& getAcceptLanguage();
    string& getUserAgent();
    string& getContentType();
    string& getHost();
    string& getContentLength();
    string& getConnect();
    string& getCache();
    string& getCookies();

    Request& setUrl(Url& url);
    Url& getUrl();
    string get();
    string post();

protected:
    virtual void defaultValue();

private:
    Url                         url;
    string                      httpVersion;
    string                      accept;
    string                      referer;
    string                      acceptLanguage;
    string                      userAgent;
    string                      contentType;
    string                      host;
    string                      contentLength;
    string                      connection;
    string                      cacheControl;
    string                      cookies;
    string                      authorization;
};
#endif
