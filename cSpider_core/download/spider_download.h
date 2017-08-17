/*************************************************************************
	> File Name: spider_download.h
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月16日 星期三 15时04分27秒
 ************************************************************************/

#ifndef _SPIDER_DOWNLOAD_H
#define _SPIDER_DOWNLOAD_H
#include <iostream>
#include <string>
#include <list>

namespace CSpider {
namespace Downloader {
    class SpiderDownloader {

    public:
        SpiderDownloader();
        ~SpiderDownloader();    

        // 下载一个页面并保存
        void download_page(const std::string url);

    protected:
        // 获取要保存的 html 路径
        std::string get_path(const std::string& path);
    private:








    };

}
}















#endif
