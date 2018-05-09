/*************************************************************************
> FileName: http.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月09日 星期三 14时44分26秒
 ************************************************************************/
#ifndef _HTTP_H
#define _HTTP_H
#include "request.h"
#include <iostream>

using namespace std;

class Http {
public:
    Http ();
    Http (Request& request);
    ~Http ();

    Http& setRequest(Request& request);
    void request();
    Request& getRequest();

protected:


private:
    string                      head;
    string*                     body;
    Request                     req;

};
#endif
