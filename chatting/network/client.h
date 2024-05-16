//
// Created by 86158 on 2024/5/14.
//

#include <winsock2.h>
#include <iostream>
#include <thread>

#include "../utils/Logger.h"

using namespace std;


/**
 * 判断两个char数组是否一致
 * @return
 */
bool compareTwoCharArray(char*, int, const char*);


void run() {
    //加载win sock2的环境
    WSADATA  wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        auto message = "WSAStartup error:" + to_string(GetLastError());
        LOG << message;
        exit(-1);
    }

    //1.创建流式套接字
    SOCKET  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        auto message = "socket error: " + to_string(GetLastError());
        LOG << message;
        exit(-1);
    }

    //2.链接服务器
    sockaddr_in   addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5031);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len = sizeof(sockaddr_in);
    if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
    {
        auto message = "connect error: " + to_string(GetLastError());
        LOG << message;
        exit(-1);
    }

    //3接收服务端的消息
    char buf[100] = { 0 };
    recv(s, buf, 100, 0);
    cout << buf << endl;

    std::thread receiveMessage([&s] () {
        int ret=0;
        do
        {
            char buf2[100] = {0};
            ret = recv(s, buf2, 100, 0);

            cout << endl << buf2 << endl;
            // print  "Please type what you want to say:";
        } while (ret!=SOCKET_ERROR && ret!=0);
    });
    receiveMessage.detach();


    //3随时给服务端发消息
    int  ret;
    do
    {
        char buf_say[100] = {0};
        cout << "Please type what you want to say:";
        cin >> buf_say;

        if (compareTwoCharArray(buf_say, 100, "exit")) {
            break;
        }

        ret = send(s, buf_say, 100, 0);
    } while (ret != SOCKET_ERROR&& ret != 0);


    //4.关闭监听套接字
    closesocket(s);

    //清理win sock2的环境
    WSACleanup();
}

bool compareTwoCharArray(char* a, int size, const char* b) {
    if (*b == '\0') {
        return false;
    }
    int i = 0;
    while (i < size && *a != *b) {
        a ++;
        i ++;
    }
    if (i >= size) {
        return false;
    }

    while (*b != '\0') {
        if (i >= size || *a != *b) {
            return false;
        }
        a ++;
        b ++;
        i ++;
    }
    return true;
}