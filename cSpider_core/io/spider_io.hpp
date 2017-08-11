/*************************************************************************
	> File Name: spider_io.hpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月10日 星期四 16时54分21秒
 ************************************************************************/

#include <iostream>
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
        SpiderIO(std::string dir, std::string file, std::string content) : dir(dir), file(file), content(content){}
        ~SpiderIO(){}

        void io_write_run() {

            // 开始写
            if(!dir_is_exist()) {

                dir_create();
            }

            file_write();
        }


    protected:
        bool dir_is_exist() {

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

        void dir_create() {

            if(dir.empty()) {

                return;
            }

            if(!mkdir(dir.c_str(), 0770)) {

                return; // 失败
            }
        }

        void file_write() {

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

            // 打开文件并执行写入操作
            fd = open(file.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0770);
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

    private:
        std::string       dir;                //  存放文件夹
        std::string       file;               //  文件名
        std::string       content;            //  内容
    
    }; // 类结束
}}
