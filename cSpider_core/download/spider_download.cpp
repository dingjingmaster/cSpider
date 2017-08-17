/*************************************************************************
	> File Name: spider_download.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月16日 星期三 15时21分11秒
 ************************************************************************/
#include <spider_download.h>
#include <spider_http.h>
#include <spider_io.h>

using namespace CSpider::Downloader;

SpiderDownloader::SpiderDownloader() {

}

SpiderDownloader::~SpiderDownloader() {

}

void SpiderDownloader::download_page(const std::string url) {

    if (url.empty()) {

        return;
    }

    CSpider::Http::SpiderHttp http(url);

    http.http_get_start();

    std::cout << http.http_get_ip() << std::endl;
    std::cout << http.http_get_request() << std::endl;

    // 保存
    CSpider::IO::SpiderIO io;
    io.io_write(get_path(http.http_get_ip()), http.http_get_request(), http.http_get_html());

    return;
}

std::string SpiderDownloader::get_path(const std::string& path) {

    if(path.empty()) {

        return "";
    }

    return std::string(path + "/html/");
}
