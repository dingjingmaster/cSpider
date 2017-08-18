/*************************************************************************
	> File Name: spider_parse.h
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月18日 星期五 14时47分17秒
 ************************************************************************/

#ifndef _SPIDER_PARSE_H
#define _SPIDER_PARSE_H

namespace CSpider {
namespace Parse {

    class SpiderParse {

    public:
        SpiderParse();
        ~SpiderParse();

        void parse_html(std::string& page);


    protected:

    };
}

}

#endif
