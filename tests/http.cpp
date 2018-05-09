/*************************************************************************
> FileName: http.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月09日 星期三 15时37分01秒
 ************************************************************************/
#include "request.h"
#include <iostream>
#include "http.h"
#include "url.h"

using namespace std;

int main (void) {
    Url     url("http://www.dingjingmaster.top/index.php/passage/03aae30dfe1f92e81969126296657daf");
    Request req(url);
    Http    http(req);

    http.request();

    return 0;
}

