/*************************************************************************
	> File Name: spider_route.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月15日 星期二 22时10分52秒
 ************************************************************************/

#include <spider_route.h>
using namespace CSpider::Route;

SpiderRoute::SpiderRoute(std::string& html){
    this->html = html;
}
SpiderRoute::~SpiderRoute(){}
        
void SpiderRoute::route_run() {

    get_url();
    //output_url();
}

void SpiderRoute::get_url() {

    int                 startNum = 0;
    int                 endNum = 0;
    int                 pos = 0;
    std::string         oo;
    std::string         buf;
    std::string         url;
    std::string         href = "<a href=";

    // 开始解析链接
    while ((endNum = html.find_first_of(href, startNum)) != std::string::npos) {

        pos = endNum;                                                   // 记录此时的位置
        startNum = endNum + 4;                                          // 移到内容后边
        endNum = html.find_first_of("\"", startNum);                    // 找到结束的位置
        if(endNum != std::string::npos) {
            url = html.substr(pos, endNum - pos);
            std::cout << url << std::endl;

            getchar();
        }

        //std::cin > oo;
        startNum = endNum + 1;
    }
}


