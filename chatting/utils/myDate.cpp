//
// Created by 86158 on 2024/4/28.
//

#include "myDate.h"
#include <sstream>


namespace morse_code_chatting::utils {
    myDate::myDate() {
        time_t now = time(nullptr);
        tm *p = localtime(&now);
        year = p->tm_year + 1900;
        month = p->tm_mon + 1;
        day = p->tm_mday;

        delete p;
    }

    std::string myDate::String() const {
        return std::string(
                std::to_string(year) + "-" +
                std::to_string(month) + "-" +
                std::to_string(day));
    }

    std::string myDate::getFullTimeForLog() {
        std::ostringstream oss;

        time_t now = time(nullptr);
        tm *p = localtime(&now);

        oss << std::to_string(p->tm_year + 1900) + ".";
        oss << std::to_string(p->tm_mon + 1) + ".";
        oss << std::to_string(p->tm_mday) + " ";

        oss << std::to_string(p->tm_hour) + ":";
        oss << std::to_string(p->tm_min) + ":";
        oss << std::to_string(p->tm_sec);

        // delete p;
        // > p 是静态分配的，不应该释放

        return oss.str();
    }

    // temp function
    // 判断字符是否是数字
    bool isDigit(char ch) {
        return ch <= '9' && ch >= '0';
    }

    // 获取年份的同时移动index
    //TODO: 恶意的年份过大处理
    int getYear(const std::string &date, int &index) {
        if (index < 0 || index >= date.length()) {
            return 0;
        }
        int year(0), flag(0);
        while (index < date.length() && isDigit(date[index])) {
            flag++;
            year = year * 10 + (date[index] - '0');
            index++;
        }
        if (index < date.length() && date[index] != '-') {
            return 0;
        }
        index++;
        if (flag < 4) {
            return 0;
        }
        return year;
    }

    int getMonthOrDay(const std::string &date, int &index) {
        if (index < 0 || index >= date.length()) {
            return 0;
        }
        // 一定要给res 初始化为0 不然res 为上一个的year
        int res(0), flag(0);
        while (index < date.length() && isDigit(date[index])) {
            flag++;
            res = res * 10 + (date[index] - '0');
            index++;
        }
        if (index < date.length() && date[index] != '-') {
            return 0;
        }
        index++;
        if (flag > 2) {
            return 0;
        }
        return res;
    }

    bool myDate::isDate(const std::string &date) {
        int index(0);
        int year = getYear(date, index);
        int month = getMonthOrDay(date, index);
        int day = getMonthOrDay(date, index);

        if (!(year || month || day)) {
            return false;
        }

        return isCorrectDate(year, month, day);
    }

    bool myDate::isCorrectDate(int year, int month, int day) {
        int monthDay[12] = {31, 28, 31, 30, 31, 30,
                            31, 31, 30, 31, 30, 31};
        if (month <= 0 || month > 12 || year <= 0 || day <= 0) {
            return false;
        }
        bool flag(false);
        if (!isLeapYear(year) || (isLeapYear(year) && month != 2)) {
            flag = (day <= monthDay[month - 1]);
        }
        else if (month == 2) {
            flag = (day <= 29);
        }
        return flag;
    }

    int myDate::dow(int year, int month, int day) {
        year -= month < 3;

        // "-bed=pen+mad." : static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4}
        return (year + year / 4 - year / 100 + year / 400 + "-bed=pen+mad."[month] + day) % 7;
    }

    std::string myDate::getCurrentDate() {
        myDate date;

        return std::string(
                std::to_string(date.year) + "-" +
                std::to_string(date.month) + "-" +
                std::to_string(date.day));
    }
} // morse_code_chatting
// utils