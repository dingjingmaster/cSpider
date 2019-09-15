#ifndef LOG_H
#define LOG_H

#include <QObject>



class Log {
public:
    Log();



public:
    /* 日志级别 */
    enum LOG_LEVEL {
        LOG_DEBUG = 0,          /* debug */
        LOG_INFO,               /* info */
        LOG_WARN,               /* warning */
        LOG_ERROR,              /* error */
    };

    /* 日志输出选项 */
    enum LOG_OUTPUT {
        LOG_OUT_CONSOLE = 0,    /* 控制台输出 */
        LOG_OUT_FILE,           /* 文件输出 */
        LOG_OUT_SOCKET,         /* socket 输出 */
    };
};

#endif // LOG_H
