/*************************************************************************
> FileName: spider_http.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 15时35分01秒
 ************************************************************************/
#include "spider_http.h"


SpiderHttp::SpiderHttp() {
    this->requestHttpInfo = new RequestHttpInfo;
    this->replyHttpInfo = new ReplyHttpInfo;
}

void SpiderHttp::setUrl(string& url) {
    if (url.length() <= 0) {
        return;
    }
    //this->url = url;
}


