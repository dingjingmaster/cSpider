/*************************************************************************
> FileName: url1.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年05月08日 星期二 16时46分46秒
 ************************************************************************/
#include "url.h"
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string      url = "http://www.dingjingmaster.top";
    Url         u("https://blog.csdn.net/u010256388/article/details/68491509");
    //Url         u(url);
    cout << "type:" << u.getType() << endl;
    cout << "host:" << u.getHost() << endl;
    cout << "port:" << u.getPort() << endl;
    cout << "ip:" << u.getIp() << endl;
    cout << "content:" << u.getContent() << endl;

    return 0;
}
