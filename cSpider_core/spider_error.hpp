/*************************************************************************
	> File Name: spider_error.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 13时31分52秒
 ************************************************************************/

#ifndef _SPIDER_ERROR_HPP
#define _SPIDER_ERROR_HPP
#include <iostream>
#include <exception>
#include <string>

namespace CSpider {
namespace Exception {

/*  类开始  */
class SpiderException : public : std::exception {
public:
    SpiderException () {}

private:

    const int SPIDER_NULL = 0;
    const int SPIDER_ERROR = 1;
    const int SPIDER_WORNG_INPUT = 2;
            
    const int SPIDER_DATA_LOSE = 3;
            
    const int SPIDER_FILE_OPEN_FAILED = 4;
    const int SPIDER_FILE_IS_EXIST = 5;
    const int SPIDER_DIRECTORY_IS_EXIST = 6;
};
}
}

#endif
