/*************************************************************************
> FileName: spider_base.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 09时55分20秒
 ************************************************************************/
#ifndef _SPIDERBASE_H
#define _SPIDERBASE_H
#include <iostream>
#include <string>
#include <queue>
#include <set>

using namespace std;

class SpiderBase {
public:
    SpiderBase();
    ~SpiderBase();
protected:

private:
    string                  url;
    set<string>             filter;
    queue<string>           urls;



};
#endif
