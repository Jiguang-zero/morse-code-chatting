//
// Created by 86158 on 2024/5/2.
//

#include "Logger.h"
#include <iostream>
#include <filesystem>
#include "myDate.h"

namespace morse_code_chatting::utils {
    const char* Logger::LOG_FILE = "log/log.txt";
    const char* Logger::LOG_PATH = "log";

    Logger* Logger::instance = nullptr;

    Logger *Logger::getInstance() {
        if (instance == nullptr) {
            instance = new Logger();
            instance->start();
        }
        return instance;
    }

    void Logger::info(const std::string &message) {
        std::lock_guard<std::mutex> lock(mtx);
        outFile << myDate::getFullTimeForLog() << " " << message << std::endl;
    }

    void Logger::start() {
        // 如果不存在 log 文件夹，则创建
        std::filesystem::path folderPath = LOG_PATH;
        if (!std::filesystem::exists(folderPath)) {
            if (!std::filesystem::create_directories(folderPath)) {
                std::cerr << "create log folder error." << std::endl;
                // exit(-1)
            }
        }

        // 打开文件输出流 追加模式
        outFile.open(LOG_FILE, std::ofstream::app);
        if (!outFile.is_open()) {
            std::cerr << "log/log.txt is not open." << std::endl;
        }
    }

    void Logger::stop() {
        outFile.close();
        if (outFile.is_open()) {
            std::cerr << "log/log.txt close failed." << std::endl;
        }
    }

    Logger *&Logger::operator<<(const std::string &message) {
        instance->info(message);

        return instance;
    }


} // morse_code_chatting
// utils