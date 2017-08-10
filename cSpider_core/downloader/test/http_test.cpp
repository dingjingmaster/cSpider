/*************************************************************************
	> File Name: http_test.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 15时08分02秒
 ************************************************************************/

#include <iostream>
#include <../spider_http.hpp>

using namespace std;
using namespace CSpider::Http;

int main(int argc, char** argv) {

    SpiderHttp http("https://wenku.baidu.com/view/a0436a1afc4ffe473368ab2b.html");
    http.http_get();





    return 0;
}

