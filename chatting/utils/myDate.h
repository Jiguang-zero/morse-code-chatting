//
// Created by 86158 on 2024/4/28.
//

#ifndef WORDS_MY_DATE_H
#define WORDS_MY_DATE_H

#include <ctime>
#include <string>

namespace morse_code_chatting::utils {

    /**
     * �Զ������ʾ����
     */
    class myDate {
    private:
        int year;
        int month;
        int day;

    private:
        /**
         * �ж����������Ƿ���ȷ
         * @param year > 0
         * @param month > 0
         * @param day > 0
         * @return bool
         */
        static bool isCorrectDate(int year, int month, int day);

    public:
        /**
         * Ĭ�Ϲ��캯��������ֻ����һ��
         */
        myDate();

        /**
         * �ж�һ������Ƿ�������
         * @param year �������Ҫ�� ����
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
         * ��ȡ��ǰ���� ���ַ���
         */
        static std::string getCurrentDate();

        /**
         * ��ȡ���ڵ��ַ�����ʾ
         * @return YYYY-MM-DD
         */
        [[nodiscard]] std::string String() const;

        /**
         * �ж������ַ����Ƿ���һ����ȷ������
         * > �����ʷ����������ж�ʱ���Ƿ����
         * @param date std::string YYYY-MM-DD
         * @return bool
         */
        static bool isDate(const std::string& date);

        /**
         * ��ȡ������ʱ�� yyyy-mm-dd hh:mm:ss ������־ϵͳʹ��
         * @return std::string ʱ���ַ��� e.g. 2024.1.5 32:23:43
         */
        static std::string getFullTimeForLog();

        /**
         * Tomohiko Sakamoto �㷨����ȡ��ǰ���������ڼ� (1582-10-15 ֮��)
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
