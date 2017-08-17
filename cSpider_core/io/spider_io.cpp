/*************************************************************************
	> File Name: spider_io.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月14日 星期一 17时39分31秒
 ************************************************************************/

#include <spider_io.h>
#include <cstring>

using namespace CSpider::IO;

SpiderIO::SpiderIO() {

}

void SpiderIO::io_write_run() {

    // 开始写
    if(!dir_is_exist()) {

        dir_create();
    }

    file_write();

    return;
}

void SpiderIO::io_write(const std::string dir, const std::string file, const std::string content) {

    if(dir.empty() || file.empty()) {

        std::cout << "io_write error!!!" << std::endl;

        return;
    }

    int     fd;
    int     ret;

    if(!dir_is_exist(dir)) {

        dir_create(dir);
    }


    // 切换目录
    if(-1 == chdir(dir.c_str())) {
                
                ////// 不存在
        return;
    }

    // 归一化文件路径
    std::string path = file_norm(file);

    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0770);
    if(-1 == fd) {
                
        return; //error
    }

    ret = write(fd, content.c_str(), content.length());
    if(ret < content.length()) {
                
        return; // error
    }

    close(fd);

    return;
}

void SpiderIO::io_write(const std::string dir, const std::string file, const char* content) {

    if(dir.empty() || file.empty() || NULL == content) {

        std::cout << "io_write error!!!" << std::endl;

        return;
    }

    int     fd;
    int     ret;

    // 是否存在
    if(!dir_is_exist()) {

        dir_create(dir);
    }


    // 切换目录
    if(-1 == chdir(dir.c_str())) {
                
                ////// 不存在
        std::cout << "切换目录错误" << std::endl;
        return;
    }

    // 归一化文件路径
    std::string path = file_norm(file);

    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0770);
    if(-1 == fd) {
                
        std::cout << "open error: " << file << std::endl;
        return; //error
    }

    std::cout << file << std::endl;

    ret = write(fd, content, strlen(content));
    if(ret < strlen(content)) {
                
        close(fd);
        return; // error
    }

    close(fd);

}

void SpiderIO::io_write(const char* dir, const char* file, const char* content) {

    if(NULL == dir || NULL == file || NULL == content) {

        std::cout << "io_write error!!!" << std::endl;

        return;
    }

    int     fd;
    int     ret;


    // 创建目录
    if(!dir_is_exist()) {

        dir_create(dir);
    }


    // 切换目录
    if(-1 == chdir(dir)) {
                
                ////// 不存在
        return;
    }

    // 归一化文件路径
    std::string path = file_norm(file);

    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0770);
    if(-1 == fd) {
                
        return; //error
    }

    ret = write(fd, content, strlen(content));
    if(ret < strlen(content)) {
                
        return; // error
    }

    close(fd);
}


bool SpiderIO::dir_is_exist() {

    if (dir.empty()) {

        return false;
    }

    int           ret;
    struct stat   dirInfo;

    if(opendir(dir.c_str()) == NULL) {

                ////////
        return false;
    }

    return true;
}

bool SpiderIO::dir_is_exist(const std::string& dir) {

    if (dir.empty()) {

        return false;
    }

    int           ret;
    struct stat   dirInfo;

    if(opendir(dir.c_str()) == NULL) {

                ////////
        return false;
    }

    return true;
}


bool SpiderIO::dir_is_exist(const char* dir) {

    if (NULL == dir) {

        return false;
    }

    int           ret;
    struct stat   dirInfo;

    if(opendir(dir) == NULL) {
        
        return false;
    }


    return true;
}


void SpiderIO::dir_create() {

    if(dir.empty()) {

        return;
    }

    if(!mkdir(dir.c_str(), 0770)) {

        return; // 失败
    }
}

void SpiderIO::dir_create(const std::string& dir) {

    if(dir.empty()) {

        return;
    }

    if(!mkdir(dir.c_str(), 0770)) {

        return; // 失败
    }
}


void SpiderIO::dir_create(const char* dir) {

    if(NULL == dir) {

        return;
    }

    if(!mkdir(dir, 0770)) {

        return; // 失败
    }
}


void SpiderIO::file_write() {

    if(file.empty()) {

        return;
    }

    int     fd;
    int     ret;

    // 切换目录
    if(-1 == chdir(dir.c_str())) {
                
                ////// 不存在
        return;
    }

    // 归一化文件路径
    std::string path = file_norm(file);


    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0770);
    if(-1 == fd) {
                
        return; //error
    }

    ret = write(fd, content.c_str(), content.length());
    if(ret < content.length()) {
                
        return; // error
    }

    close(fd);

    return;
}


std::string SpiderIO::file_norm(const std::string& file) {
    
    if(file.empty()) {

        return "";
    }

    // 开始转化
    int   ret = 0;
    int   pathLen = file.length();
    char  path[1024] = {0};

    if(pathLen >= 1024) {
        pathLen = 1023;
    }

    strncpy(path, file.c_str(), pathLen);

    for (int i = 0; i < pathLen; ++i) {
        if(path[i] == '/') {
            path[i] = '_';
        }
    }


    return path;
}


std::string SpiderIO::file_norm(const char* file) {
    
    if(NULL == file) {

        return "";
    }

    // 开始转化
    int   ret = 0;
    int   pathLen = strlen(file);
    char  path[1024] = {0};

    if(pathLen >= 1024) {
        pathLen = 1023;
    }

    strncpy(path, file, pathLen);

    for (int i = 0; i < pathLen; ++i) {
        if(path[i] == '/') {
            path[i] = '_';
        }
    }


    return path;
}





