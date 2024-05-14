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
     * ʵ����־��
     * �̰߳�ȫ�ĵ���ģʽ
     */
    class Logger {
    private:
        /**
         * ���캯����˽�У���ʼ�� instance
         */
        Logger() = default;

        /**
         * ����������˽��   ����stop()�������ر��ļ���
         */
        ~Logger() {
            stop();
        }

        static Logger* instance;

    public:
        // ɾ�� auto b = a ���ָ���
        const Logger &operator=(const Logger & _logger) = delete;

        // ɾ�� Ĭ�Ϲ��� auto a(b) ���ָ���
        Logger(const Logger& _logger) = delete;

    private:
        // ȫ����־�ļ��Ĵ洢
        const static char* LOG_FILE;

        // ȫ����־�ļ����ļ��� log
        const static char* LOG_PATH;

        std::ofstream outFile;
        // ������(�̰߳�ȫ)
        std::mutex mtx;


    public:
        /**
         * �ع� <<
         * @param message const std::string&
         * @return Logger& �ع� << ���ţ�ʵ��info(message) �Ĺ��ܣ�����ʹ�ú�
         */
        Logger*& operator << (const std::string & message);

        /**
         * ��ȡ instance
         * @return Logger*
         */
        static Logger* getInstance();

        /**
         * ����־�ļ���Ϣ�洢���ļ���
         * @param message const std::string&
         */
        void info(const std::string& message);

        // ����־�ļ� ��
        void start();

        // �ر���־�ļ� ��
        void stop();

    };

} // morse_code_chatting
// utils

// ����꣬ʵ�ֿ��ٵ�ʵ����־����
#ifndef LOG_GLOBAL
#define LOG *morse_code_chatting::utils::Logger::getInstance()
#endif //LOG_GLOBAL

#endif //WORDS_LOGGER_H
