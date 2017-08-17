/*************************************************************************
	> File Name: spider_main.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月14日 星期一 17时28分20秒
 ************************************************************************/

#include <iostream>
#include <spider_io.h>
#include <spider_download.h>
#include <spider_route.h>
#include <vector>

using namespace std;
using namespace CSpider;
using namespace CSpider::Downloader;
using namespace CSpider::Route;
using namespace CSpider::IO;


int main(int argc, char* argv[]) {

    SpiderDownloader  d;
    SpiderRoute       r;
    SpiderIO          io;
    vector<string>    v;

    d.download_page("http://blog.csdn.net/grandPang/article/details/47448395");

    // blog.csdn.net/html/grandPang_article_details_47448395
    //r.get_url("blog.csdn.net/html/grandPang_article_details_47448395", v);
    io.io_read("blog.csdn.net/html/grandPang_article_details_47448395", v);

    // 文件所有行数
    for(vector<string>::iterator it = v.begin(); it != v.end(); ++it) {

        cout << *it << endl;
    }


    cout << "完成" << endl;



    return 0;
}

