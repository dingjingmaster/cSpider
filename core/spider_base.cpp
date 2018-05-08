/*************************************************************************
> FileName: spider_base.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 09时55分14秒
 ************************************************************************/
#include "spider_base.h"
#include "spider_http.h"

SpiderBase::SpiderBase() {
    filter = new set<string>();
    urls = new queue<string>();
}


SpiderBase::~SpiderBase() {
    delete[] filter;
    delete[] urls;
}


void SpiderBase::setUrl(string& url) {
    if (url.length() <= 0) {
        return;
    }
    this->url = url;
}


string SpiderBase::getHtml() {
}


string SpiderBase::parseContent() {
}
