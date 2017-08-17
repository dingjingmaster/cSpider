/*************************************************************************
	> File Name: spider_global.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月16日 星期三 15时59分45秒
 ************************************************************************/

#ifndef _SPIDER_GLOBAL_HPP
#define _SPIDER_GLOBAL_HPP
#include <iostream>
#include <map>
#include <list>

namespace CSpider {


    // 过滤器 
    std::map<std::string, std::string>  globalFilter;

    // 解析队列
    std::list<std::string>  globalParseList;
    
    // 下载队列
    std::list<std::string>  globalDownloadList;




}












#endif
