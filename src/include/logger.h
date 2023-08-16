#pragma once
#include "lockqueue.h"
#include <string>
enum LogLevel
{

    INFO, //
    ERROR,
};

// mprpc框架提供的日志系统：
class Logger
{
public:
    // 获取日志的单例
    static Logger &GetInstance();
    // 设置日志的级别：
    void SetLogLevel(LogLevel level);
    // 写日志
    void Log(std::string msg);

private:
    int m_loglevel;                  // 记录日志的级别；
    LockQueue<std::string> m_lckQue; // 日志缓冲队列
    Logger();
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
};

// 定义宏
#define LOG_INFO(logmsgfromat, ...)                     \
    do                                                  \
    {                                                   \
        Logger &logger = Logger::GetInstance();         \
        logger.SetLogLevel(INFO);                       \
        char c[1024] = {0};                             \
        snprintf(c, 1024, logmsgfromat, ##__VA_ARGS__); \
        logger.Log(c);                                  \
    } while (0);
;

#define LOG_ERR(logmsgfromat, ...)                      \
    do                                                  \
    {                                                   \
        Logger &logger = Logger::GetInstance();         \
        logger.SetLogLevel(ERROR);                      \
        char c[1024] = {0};                             \
        snprintf(c, 1024, logmsgfromat, ##__VA_ARGS__); \
        logger.Log(c);                                  \
    } while (0);
;