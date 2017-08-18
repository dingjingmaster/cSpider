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
    std::string                 baseUrl;
    std::string                 href1 = "<a href=";
    std::string                 href2 = "<a href =";
    std::string                 baseUrl1 = "base href=";
    std::string                 baseUrl2 = "base href =";
    std::string                 flag1 = "\'";
    std::string                 flag2 = "\"";
    SpiderIO                    io;
    std::vector<std::string>    v;

    io.io_read(htmlFile.c_str(), v);

    for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {

        startPos = 0;
        endPos = 0;

        // check up base url
        while((endPos = it->find(baseUrl1, startPos)) != std::string::npos || (endPos = it->find(baseUrl1, startPos)) != std::string::npos) {

            int pos1 = 0;
            int pos2 = 0;

            //std::cout << *it << std::endl;

            // find first href1
            if((pos1 = it->find_first_of(flag1, endPos)) != std::string::npos) {

                // find url
                pos2 = it->find_first_of(flag1, pos1 + 1);
                pos2 = it->find_first_of(flag2, pos1 + 1);
                if(pos2 > pos1 && pos1 != std::string::npos && pos2 != std::string::npos) {

                    baseUrl = it->substr(pos1 + 1, pos2 - pos1 - 1);

                    std::cout << baseUrl << std::endl;
                    std::cout << "\n\n" << std::endl;

                    startPos = pos2;
                    continue;
                }

            }


            // find first href1
            if((pos1 = it->find_first_of(flag2, endPos)) != std::string::npos) {

                // find url
                pos2 = it->find_first_of(flag1, pos1 + 1);
                pos2 = it->find_first_of(flag2, pos1 + 1);
                if(pos2 > pos1 && pos1 != std::string::npos && pos2 != std::string::npos) {

                    baseUrl = it->substr(pos1 + 1, pos2 - pos1 - 1);

                    std::cout << baseUrl << std::endl;
                    //std::cout << "\n\n" << std::endl;
            
                    startPos = pos2;
                    continue;
                }
            }
        }


        // check up 
        startPos = 0;
        endPos = 0;
        while((endPos = it->find(href1, startPos)) != std::string::npos || (endPos = it->find(href2, startPos)) != std::string::npos) {

            int pos1 = 0;
            int pos2 = 0;

            //std::cout << *it << std::endl;

            // find first href1
            if((pos1 = it->find_first_of(flag1, endPos)) != std::string::npos) {

                // find url
                pos2 = it->find_first_of(flag1, pos1 + 1);
                pos2 = it->find_first_of(flag2, pos1 + 1);
                if(pos2 > pos1 && pos1 != std::string::npos && pos2 != std::string::npos) {

                    url = it->substr(pos1 + 1, pos2 - pos1 - 1);

                    //std::cout << url << std::endl;
                    //std::cout << "\n\n" << std::endl;

                    startPos = pos2;
                    continue;
                }

            }

            // find first href1
            if((pos1 = it->find_first_of(flag2, endPos)) != std::string::npos) {

                // find url
                pos2 = it->find_first_of(flag1, pos1 + 1);
                pos2 = it->find_first_of(flag2, pos1 + 1);
                if(pos2 > pos1 && pos1 != std::string::npos && pos2 != std::string::npos) {

                    url = it->substr(pos1 + 1, pos2 - pos1 - 1);

                    //std::cout << url << std::endl;
                    //std::cout << "\n\n" << std::endl;
            
                    startPos = pos2;
                    continue;
                }
            }
        }


    }
}






























