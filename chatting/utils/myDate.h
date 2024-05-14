//
// Created by 86158 on 2024/4/28.
//

#ifndef WORDS_MY_DATE_H
#define WORDS_MY_DATE_H

#include <ctime>
#include <string>

namespace morse_code_chatting::utils {

    /**
     * 自定义类表示日期
     */
    class myDate {
    private:
        int year;
        int month;
        int day;

    private:
        /**
         * 判断所给日期是否正确
         * @param year > 0
         * @param month > 0
         * @param day > 0
         * @return bool
         */
        static bool isCorrectDate(int year, int month, int day);

    public:
        /**
         * 默认构造函数，有且只能这一个
         */
        myDate();

        /**
         * 判断一个年份是否是闰年
         * @param year 必须符合要求 正数
         * @return
         */
        static bool isLeapYear(int year) {
            // year / 4 - year / 100 + year / 400
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                return true;
            } else {
                return false;
            }
        }

        /*
         * 获取当前日期 的字符串
         */
        static std::string getCurrentDate();

        /**
         * 获取日期的字符串表示
         * @return YYYY-MM-DD
         */
        [[nodiscard]] std::string String() const;

        /**
         * 判断所给字符串是否是一个正确的日期
         * > 仅做词法分析，不判断时间是否合理
         * @param date std::string YYYY-MM-DD
         * @return bool
         */
        static bool isDate(const std::string& date);

        /**
         * 获取完整的时间 yyyy-mm-dd hh:mm:ss 用于日志系统使用
         * @return std::string 时间字符串 e.g. 2024.1.5 32:23:43
         */
        static std::string getFullTimeForLog();

        /**
         * Tomohiko Sakamoto 算法，获取当前日期是星期几 (1582-10-15 之后)
         * @param year
         * @param month
         * @param day
         * @return int
         */
        static int dow(int year, int month, int day);
    };

} // morse_code_chatting
// utils

#endif //WORDS_MY_DATE_H
