/*************************************************************************
> FileName: url.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 15时52分19秒
 ************************************************************************/
#include "url.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

Url::Url() {
}


Url::Url(string url) {
    if(url.length() > 0) {
        this->url = url;
    }
    parseUrl();
}


void Url::setUrl(string url) {
    if(url.length() > 0) {
        this->url = url;
    }
    parseUrl();
}


Url::~Url() {
}


string& Url::getType() {
    if(type.length() <= 0) {
        ///
    }
    return type;
}


string& Url::getHost() {
    if(host.length() <= 0) {
        ///
    }
    return host;
}


string& Url::getPort() {
    if(port.length() <= 0) {
        ///
    }
    return port;
}


string& Url::getIp() {
    if(ip.length() <= 0) {
        ///
    }
    return ip;
}


string& Url::getContent() {
    if(content.length() <= 0) {
        ///
    }
    return content;
}



void Url::parseUrl() {
    int                     startNum = 0;
    int                     endNum = 0;
    char                    tmpStr[64] = {0};
    struct hostent*         tip;
    
    // type 
    endNum = url.find_first_of("//", startNum);
    if(endNum != string::npos) {
        endNum -= startNum;
        type = url.substr (startNum, endNum - 1);
        startNum += endNum;
        startNum += 2;
    }

    // host
    endNum = url.find_first_of(":", startNum);
    if (endNum != string::npos) {
        endNum -= startNum;
        host = url.substr(startNum, endNum);
        startNum += endNum;
        ++ startNum;
        endNum = url.find_first_of("/", startNum);
        if(endNum != string::npos) {
            endNum == startNum;
            port = url.substr(startNum, endNum);
            startNum += endNum;
            ++ startNum;
        } else {
            port = url.substr(startNum, url.length());
            startNum = url.length();
        }
    } else { 
        endNum = url.find_first_of("/", startNum);
        if(endNum != string::npos) {
            endNum -= startNum;
            host = url.substr(startNum, endNum);
            startNum += endNum;
            ++ startNum;
        } else {
            host = url.substr(startNum, url.length());
            startNum = url.length();
        }
    }

    // content
    if(startNum >= url.length()) {
        content = "/";
    } else {
        content = "/" + url.substr(startNum, url.length());
    }

    tip = gethostbyname(host.c_str());
    if(NULL != tip) {
        switch(tip->h_addrtype) {
            case AF_INET:
            case AF_INET6:
                inet_ntop(tip->h_addrtype, (struct in_addr*)(tip->h_addr_list[0]), tmpStr, sizeof(tmpStr));
                break;
            default:
                cout << "未知的地址类型" << endl;
                break;
        }
        ip = tmpStr;
    } else {
        ///
    }
}
