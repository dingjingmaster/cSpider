/*************************************************************************
	> File Name: download_test.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月16日 星期三 17时11分19秒
 ************************************************************************/

#include <iostream>
#include <spider_download.h>
using namespace std;
using namespace CSpider::Downloader;

int main(int argc, char** argv) {

    //SpiderHttp http("https://wenku.baidu.com/view/a0436a1afc4ffe473368ab2b.html");
    SpiderDownloader d;

    d.download_page("http://blog.csdn.net/grandPang/article/details/47448395");




    return 0;
}

