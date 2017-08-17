/*************************************************************************
	> File Name: spider_route.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月15日 星期二 22时10分52秒
 ************************************************************************/

#include <spider_route.h>
#include <spider_io.h>
#include <vector>
#include <iostream>

using namespace CSpider::Route;
using namespace CSpider::IO;

SpiderRoute::SpiderRoute() {}
SpiderRoute::~SpiderRoute(){}
        
void SpiderRoute::get_url(const std::string htmlFile, std::vector<std::string>& vurl) {

    if(htmlFile.empty()) {

        return;
    }

    int                         startPos = 0;
    int                         endPos = 0;
    std::string                 url;
    std::string                 href1 = "<a href=";
    SpiderIO                    io;
    std::vector<std::string>    v;

    io.io_read(htmlFile.c_str(), v);


    for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {

        // 获取一个连接
        endPos = (*it).find_first_of(href1.c_str(), startPos);
        if(std::string::npos != endPos) {

            std::cout << *it << std::endl;
            std::cout << "\n\n" << std::endl;
        }

        endPos = startPos;
        startPos = endPos + 1;
    }
}


void find_sub(const std::string& line, std::vector<std::string>& subStr) {

    if(line.empty()) {

        return;
    }

    int     startPos = 0;
    int     endPos = 0;

    subStr.clear();



    

}
