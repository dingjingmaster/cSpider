/*************************************************************************
	> File Name: spider_route.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月15日 星期二 22时10分52秒
 ************************************************************************/

#include <spider_route.h>
#include <iostream>
#include <fstream>

using namespace CSpider::Route;

SpiderRoute::SpiderRoute() {}
SpiderRoute::~SpiderRoute(){}
        
void SpiderRoute::get_url(const std::string htmlFile, std::vector<std::string>& vurl) {

    if(htmlFile.empty()) {

        return;
    }

    int                 startNum = 0;
    int                 endNum = 0;
    int                 pos = 0;
    std::string         oo;
    std::string         buf;
    std::string         url;
    std::string         href = "<a href=";

    std::ifstream       fin(htmlFile.c_str());
    std::string         line;

    if(fin.is_open()){
        std::cout << "打开" << std::endl;
    };

    while(getline(fin, line)) {

        std::cout << line << std::endl;

    }






    // 开始解析链接
    //while ((endNum = html.find_first_of(href, startNum)) != std::string::npos) {

    //    pos = endNum;                                                   // 记录此时的位置
    //    startNum = endNum + 4;                                          // 移到内容后边
    //    endNum = html.find_first_of("\"", startNum);                    // 找到结束的位置
    //    if(endNum != std::string::npos) {
    //        url = html.substr(pos, endNum - pos);
    //        std::cout << url << std::endl;

    //        getchar();
    //    }

        //std::cin > oo;
    //    startNum = endNum + 1;
    //}
}


