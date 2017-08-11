/*************************************************************************
	> File Name: route_test.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月11日 星期五 16时01分02秒
 ************************************************************************/

#include <iostream>
#include <spider_http.hpp>
#include <spider_route.hpp>

int main(int argc, char** argv) {

    CSpider::Http::SpiderHttp http("http://blog.csdn.net/grandPang/article/details/47448395");
    http.http_get_start();

    std::string html = http.http_get_html();
    int len = html.length();

    //std::cout << html << std::endl;
    
    CSpider::Route::SpiderRoute route(html);
    route.route_run();

    //std::cout << http.http_get_html() << std::endl;


}

