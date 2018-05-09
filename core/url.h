/*************************************************************************
> FileName: url.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 15时52分05秒
 ************************************************************************/
#ifndef _URL_H
#define _URL_H
#include <iostream>
#include <string>

using namespace std;

class Url {
public:
    Url();
    Url(string url);
    ~Url();
    void setUrl(string url);
    string& getType();
    string& getHost();
    string& getPort();
    string& getIp();
    string& getContent();
    short int getAddrType();

protected:
    virtual void parseUrl();

private:
    short int       addrType;
    string          url;
    string          type;
    string          host;
    string          port;
    string          ip;
    string          content;
};
#endif
