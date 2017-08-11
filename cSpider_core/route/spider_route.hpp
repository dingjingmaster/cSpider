/*************************************************************************
	> File Name: spider_route.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月11日 星期五 14时31分11秒
 ************************************************************************/

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
#include <cstring>







namespace CSpider {
namespace Route {
    class SpiderRoute {

    public:
        SpiderRoute(const char* pHtml, const int htmlLen) : pHtml(pHtml), htmlLen(htmlLen){}
        ~SpiderRoute(){}
        
        void route_run() {

            get_url();
            output_url();
        }

    protected:
        void get_url() {

            char buf[1024] = {0};
            std::string url;

            // 同时查找 href base href
            for(int i = 0; i < htmlLen - 14; ++i) {

                // 找到一天链接
                if(0 == strncmp(pHtml + i, "href=", 5) || 0 == strncmp(pHtml + i, "href =", 6)) {

                    // 找到引号
                    int       len = 0;
                    char*     pHead = pHtml + i;
                    char*     pEnd = NULL;

                    // 开始解析 ---
                    while(*(++ pHead) != '\"' && *(++ pHead) != '\'');
                    pEnd = ++ pHead;
                    while(*(++ pEnd) != '\"' && *(++ pEnd) != '\'');

                    // 去头尾
                    if(*pHead == '\'' || *pHead == '\"')
                        ++pHead;
                    if(*pEnd == '\'' || *pEnd == '\"')
                        --pEnd;

                    len = pEnd - pHead;

                    // 保存链接
                    memset(buf, 0, sizeof(buf));
                    strncmp(buf, pHead, len);
                    url = buf;

                    urlList.append(url);
                    i += len;

                }

                // 找到一条 base 链接
                if(0 == strncmp(pHtml + i, "base href=", 10) || 0 == strncmp(pHtml + i, "base href =", 11)) {

                    // 找到引号
                    int       len = 0;
                    char*     pHead = pHtml + i;
                    char*     pEnd = NULL;

                    // 开始解析 ---
                    while(*(++ pHead) != '\"' && *(++ pHead) != '\'');
                    pEnd = ++ pHead;
                    while(*(++ pEnd) != '\"' && *(++ pEnd) != '\'');

                    // 去头尾
                    if(*pHead == '\'' || *pHead == '\"')
                        ++pHead;
                    if(*pEnd == '\'' || *pEnd == '\"')
                        --pEnd;

                    len = pEnd - pHead;

                    // 保存链接
                    memset(buf, 0, sizeof(buf));
                    strncmp(buf, pHead, len);
                    url = buf;

                    baseUrlList.append(url);
                    i += len;
                }
            }
        } // get_url 结束

        // url 简单处理
        void dispose_url() {

            
        } // url 处理结束

        void output_url() {

            for(std::list<std::string>::iterator it = urlList.begin(); it != urlList.end(); ++ it) {

                std::cout << "url: " << *it << std::endl;
            }
            
        }


    private:
        const char*             pHtml;
        const int               htmlLen;
        std::list<std::string>  urlList;
        std::list<std::string>  baseUrlList;


    }; // 类结束
}
}




























































