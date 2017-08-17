/*************************************************************************
	> File Name: spider_io.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月14日 星期一 17时39分31秒
 ************************************************************************/

#include <spider_io.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>

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

    // 归一化文件路径
    std::string path = file_norm(dir, file);

    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0660);
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

    // 归一化文件路径
    std::string path = file_norm(dir, file);

    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0660);
    if(-1 == fd) {
                
        std::cout << "open error: " << file << std::endl;
        return; //error
    }

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

    // 归一化文件路径
    std::string path = file_norm(dir, file);

    // 打开文件并执行写入操作
    fd = open(path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0660);
    if(-1 == fd) {
                
        return; //error
    }

    ret = write(fd, content, strlen(content));
    if(ret < strlen(content)) {
                
        return; // error
    }

    close(fd);
}


void SpiderIO::io_read(const char* file, std::vector<std::string>& page) {

    if(NULL == file) {

        return;
    }

    int           fd;
    char          buf;
    std::string   line;
    
    fd = open(file, O_RDONLY);

    while(0 < read(fd, &buf, 1)) {

        if(buf == '\n') {

            page.push_back(line);

            line.clear();

            continue;
        }
        
        line += buf;
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

    std::string path;
    std::vector<std::string>  vpath;

    // 对文件夹进行分割
    string_split(dir, "/", vpath);

    for(std::vector<std::string>::iterator it = vpath.begin(); it != vpath.end(); ++it) {

        if((*it).empty()) {
            continue;
        }

        path += *it;
        mkdir(path.c_str(), 0770);
        path += "/";
    }
}

void SpiderIO::dir_create(const std::string& dir) {

    if(dir.empty()) {

        return;
    }

    std::string path;
    std::vector<std::string>  vpath;

    // 对文件夹进行分割
    string_split(dir, "/", vpath);

    for(std::vector<std::string>::iterator it = vpath.begin(); it != vpath.end(); ++it) {

        if((*it).empty()) {
            continue;
        }

        path += *it;
        mkdir(path.c_str(), 0770);
        path += "/";
    }
}


void SpiderIO::dir_create(const char* dir) {

    if(NULL == dir) {

        return;
    }

    std::string path;
    std::vector<std::string>  vpath;

    // 对文件夹进行分割
    string_split(dir, "/", vpath);

    for(std::vector<std::string>::iterator it = vpath.begin(); it != vpath.end(); ++it) {

        if((*it).empty()) {
            continue;
        }

        path += *it;
        mkdir(path.c_str(), 0770);
        path += "/";
    }
}


void SpiderIO::file_write() {

    if(file.empty()) {

        return;
    }

    int     fd;
    int     ret;

    // 归一化文件路径
    std::string path = file_norm(dir, file);


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


std::string SpiderIO::file_norm(const std::string dir, const std::string& file) {
    
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


    return dir + "/" + std::string(path);
}


std::string SpiderIO::file_norm(const char* dir, const char* file) {
    
    if(NULL == file) {

        return "";
    }

    // 开始转化
    int   ret = 0;
    int   pathLen = strlen(file);
    char  fpath[2048] = {0};
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

    strncat(fpath, dir, 2048);
    strncat(fpath, path, 2048);

    return fpath;
}

void SpiderIO::string_split(const std::string str, const std::string split, std::vector<std::string>& v) {
    if(str.empty() || split.empty())
    {
        return;
            
    }

    int     found = 0;
    int     last_off = 0;
    v.clear();

    found = str.find_first_of(split);
    while(found != std::string::npos)
    {
        v.push_back(str.substr(last_off, found - last_off));
        last_off = found + 1;
        found = str.find_first_of(split, last_off);
            
    }

    if(last_off <= str.length())
    {
        v.push_back(str.substr(last_off, str.length() - last_off));
    }

    return;
}






