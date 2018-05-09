/*************************************************************************
> FileName: request.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月09日 星期三 14时24分25秒
 ************************************************************************/
#include "request.h"
#include "url.h"
#include <iostream>
using namespace std;

int main(void) {
    Url             url("http://www.uu234.net/b10/");
    Request         re;

    re.setUrl(url);

    cout << re.get() << "|" << endl;;


    return 0;
}

