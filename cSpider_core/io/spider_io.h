/*************************************************************************
	> File Name: spider_io.h
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 16时54分21秒
 ************************************************************************/
#ifndef _SPIDER_IO_H
#define _SPIDER_IO_H
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

namespace CSpider {
namespace IO {

    /*  类开始  */
    class SpiderIO {
    public:
        SpiderIO();
        SpiderIO(const std::string dir, const std::string file, const std::string content):dir(dir),file(file),content(content){}
        ~SpiderIO(){}

        void io_write(const std::string dir, const std::string file, const std::string content);
        void io_write(const std::string dir, const std::string file, const char* content);
        void io_write(const char* dir, const char* file, const char* content);
        
        void io_read(const char* file, std::vector<std::string>& page);
        void io_read(const char* file, std::string& page);

        void io_write_run(); 
        

    protected:
        bool dir_is_exist();
        bool dir_is_exist(const std::string& dir);
        bool dir_is_exist(const char* dir);
        void dir_create();
        void dir_create(const char* dir);
        void dir_create(const std::string& dir);
        void file_write(); 
        std::string file_norm(const std::string dir, const std::string& file);
        std::string file_norm(const char* dir, const char* file);
        void string_split(const std::string str, const std::string split, std::vector<std::string>& v);

    private:
        std::string       dir;                //  存放文件夹
        std::string       file;               //  文件名
        std::string       content;            //  内容
    
    }; // 类结束
}}
#endif
