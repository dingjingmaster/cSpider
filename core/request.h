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
    ~Request();
protected:

private:
    Url             url;

};
#endif
