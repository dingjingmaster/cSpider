/*************************************************************************
	> File Name: io_test.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月11日 星期五 11时23分33秒
 ************************************************************************/

#include <iostream>
#include <spider_io.h>

using namespace CSpider::IO;
using namespace std;

int main(int argc, char** argv) {

    std::string dir = "./dir";
    std::string file = "./file.txt";
    std::string content = "hello";

    SpiderIO io(dir, file, content);

    io.io_write_run();


    return 0;
}
