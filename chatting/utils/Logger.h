//
// Created by 86158 on 2024/5/2.
//

#ifndef WORDS_LOGGER_H
#define WORDS_LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

namespace morse_code_chatting::utils {

    /**
     * 实现日志类
     * 线程安全的单例模式
     */
    class Logger {
    private:
        /**
         * 构造函数，私有，初始化 instance
         */
        Logger() = default;

        /**
         * 析构函数，私有   调用stop()方法，关闭文件流
         */
        ~Logger() {
            stop();
        }

        static Logger* instance;

    public:
        // 删除 auto b = a 这种复制
        const Logger &operator=(const Logger & _logger) = delete;

        // 删除 默认构造 auto a(b) 这种复制
        Logger(const Logger& _logger) = delete;

    private:
        // 全局日志文件的存储
        const static char* LOG_FILE;

        // 全局日志文件的文件夹 log
        const static char* LOG_PATH;

        std::ofstream outFile;
        // 互斥锁(线程安全)
        std::mutex mtx;


    public:
        /**
         * 重构 <<
         * @param message const std::string&
         * @return Logger& 重构 << 符号，实现info(message) 的功能，方便使用宏
         */
        Logger*& operator << (const std::string & message);

        /**
         * 获取 instance
         * @return Logger*
         */
        static Logger* getInstance();

        /**
         * 将日志文件消息存储到文件中
         * @param message const std::string&
         */
        void info(const std::string& message);

        // 打开日志文件 流
        void start();

        // 关闭日志文件 流
        void stop();

    };

} // morse_code_chatting
// utils

// 定义宏，实现快速的实现日志功能
#ifndef LOG_GLOBAL
#define LOG *morse_code_chatting::utils::Logger::getInstance()
#endif //LOG_GLOBAL

#endif //WORDS_LOGGER_H
