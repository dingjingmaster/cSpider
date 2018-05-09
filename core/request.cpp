/*************************************************************************
> FileName: request.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月09日 星期三 10时06分27秒
 ************************************************************************/
#include "request.h"

Request::Request() {
    defaultValue();
}


Request::Request(Url& url) {
    this->url = url;
    defaultValue();
}


Request::~Request() {
}


Request& Request::setUrl(Url& url) {
    this->url = url;

    return *this;
}


string Request::get() {
    string request = "";
    request += "GET " + url.getContent() + " " + httpVersion + "\r\n";
    request += "Host: " + url.getIp() + "\r\n";
    if (accept.length() > 0) {
        request += "Accept: " + accept + "\r\n";
    }
    if (referer.length() > 0) {
        request += "Referer: " + referer + "\r\n";
    }
    if (acceptLanguage.length() > 0) {
        request += "Accept-Language: " + acceptLanguage + "\r\n";
    }
    if (userAgent.length() > 0) {
        request += "User-Agent: " + userAgent + "\r\n";
    }
    if (authorization.length() > 0) {
        request += "Authorization: " + authorization + "\r\n";
    }
    if (contentType.length() > 0) {
        request += "Content-Type: " + contentType + "\r\n";
    }
    if (contentLength.length() > 0) {
        request += "ContentLength: " + contentLength + "\r\n";
    }
    if (connection.length() > 0) {
        request += "Connection: " + connection + "\r\n";
    }
    if (cacheControl.length() > 0) {
        request += "Cache-Control: " + cacheControl + "\r\n";
    }
    if (cookies.length() > 0) {
        request += "Cookies: " + cookies + "\r\n";
    }
    request += "\r\n";

    return request;
}


string Request::post() {
}


Request& Request::setHttpVersion(string version) {
    if (version.length() <= 0) {
    }
    httpVersion = version;

    return *this;
}


Request& Request::setAccept(string accept) {
    if (accept.length() <= 0) {
    }
    this->accept = accept;

    return *this;
}


Request& Request::setReferer(string referer) {
    if (referer.length() <= 0) {
    }
    this->referer = referer;

    return *this;
}


Request& Request::setAcceptLanguage(string language) {
    if (language.length() <= 0) {
    }
    acceptLanguage = language;

    return *this;
}


Request& Request::setUserAgent(string agent) {
    if (agent.length() <= 0) {
    }
    userAgent = agent;

    return *this;
}


Request& Request::setContentType(string content) {
    if (content.length() <= 0) {
    }
    contentType = content;

    return *this;
}


Request& Request::setHost(string host) {
    if (host.length() <= 0) {
    }
    this->host = host;

    return *this;
}


Request& Request::setContentLength(string contentLength) {
    if(contentLength.length() <= 0) {
    }
    this->contentLength = contentLength;

    return *this;
}


Request& Request::setConnect(string connect) {
    if (connect.length() <= 0) {
    }
    connection = connect;

    return *this;
}


Request& Request::setCache(string cache) {
    if (cache.length() <= 0) {
    }
    cacheControl = cache;

    return *this;
}


Request& Request::setCookies(string cookies) {
    if (cookies.length() <= 0) {
    }
    this->cookies = cookies;

    return *this;
}


string& Request::getHttpVersion() {

    return httpVersion;
}


string& Request::getAccept() {

    return accept;
}


string& Request::getReferer() {

    return referer;
}


string& Request::getAcceptLanguage() {

    return acceptLanguage;
}


string& Request::getUserAgent() {

    return userAgent;
}


string& Request::getContentType() {

    return contentType;
}


string& Request::getHost() {

    return host;
}


string& Request::getContentLength() {

    return contentLength;
}


string& Request::getConnect() {

    return connection;
}


string& Request::getCache() {

    return cacheControl;
}


string& Request::getCookies() {

    return cookies;
}


void Request::defaultValue() {
    httpVersion = "HTTP/1.1";
    accept = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8";
    authorization = "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==";
    //Accept-Encoding: gzip, deflate
    acceptLanguage = "zh,zh-TW;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6";
    userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36";
    cacheControl = "no-cache";
    connection = "keep-alive";
}



