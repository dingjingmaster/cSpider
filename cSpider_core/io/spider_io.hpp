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


namespace CSpider {
namespace IO {

    /*  类开始  */
    class SpiderIO {

    public:
        SpiderIO(std::string dir, std::string file, std::string content):dir(dir):file(file):content(content){}

    private:
    std::string       dir;                //  存放文件夹
    std::string       file;               //  文件名
    std::string       content;            //  内容

    protected:
        true dir_is_exist(const std::string& dir) {

            int           ret;
            struct stat   dirInfo;

            if(dir.empty()) {

                ////////
                return false;
            }

            if(opendir(dir.c_str()) == NULL) {

                ////////
                return false;
            }

            return true;
        }

        void dir_create(const std::string dir) {

            if(dir.empty()) {

                return;
            }

            if(!mkdir(dir.c_str(), 0770)) {

                return; // 失败
            }
        }

        void file_write(const std::string filePath, std::string content) {

            if(filePath.empty || content.empty) {
                
                return; // 错误
            }

            int     fd;
            // 打开文件并执行写入操作
            fd = open(filePath.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0770);
            if(-1 == fd) {
                
                return; //error
            }
            
            
        }


    
    }; // 类结束
}
}

