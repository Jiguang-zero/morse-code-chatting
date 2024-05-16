//
// Created by 86158 on 2024/5/14.
//

#include <winsock2.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

// ws2_32.lib

static vector<SOCKET> users;

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);

// 将用户的对话加上用户 id
void getMessageWithUserName(char*& res, char* buf, unsigned long long int user);

int main() {
    WSADATA wd;
    if(WSAStartup(MAKEWORD(2,2), &wd) != 0)
    {
        cout << "WSAStartup Error:" << WSAGetLastError() << endl;
        return 0;
    }

    // 1. 创建流式套接字
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s == INVALID_SOCKET)
    {
        cout << "socket error:" << WSAGetLastError() << endl;
        return 0;
    }

    // 2. 绑定端口和ip
    sockaddr_in addr{};
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5031);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len = sizeof(sockaddr_in);
    if(bind(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
    {
        cout << "bind Error:" << WSAGetLastError() << endl;
        return 0;
    }

    // 3. 监听
    listen(s,5);

    thread connectClient([&] () {
        while(true)
        {
            sockaddr_in addrClient{};
            len = sizeof(sockaddr_in);
            // 4.接受成功返回与client通讯的Socket
            SOCKET c = accept(s, (SOCKADDR*)&addrClient, &len);
            if(c != INVALID_SOCKET)
            {
                // 创建线程，并且传入与client通讯的套接字
                HANDLE hThread = CreateThread(nullptr, 0, ThreadFun, (LPVOID)c, 0, NULL);
                CloseHandle(hThread); // 关闭对线程的引用
            }
            else {
                break;
            }
        }
    } );

    connectClient.detach();

    // 主线程循环接收客户端的连接

    while (true) {
        string command;
        cin >> command;
        if (command == "exit") {
            break;
        }
    }

    // 6.关闭监听套接字
    closesocket(s);

    // 清理win sock2的环境
    WSACleanup();

    return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{
    // 5.与客户端通讯，发送或者接受数据
    auto c= (SOCKET)lpThreadParameter;

    char buf[100] = {0};
    // 人数超过两人则无法进入
    if (users.size() >= 2) {
        sprintf(buf, "There can be only two person!");
        send(c, buf, 100, 0);
        return 0;
    }

    users.emplace_back(c);

    cout << "Welcome " << c << " enter the room!" << endl;


    // 循环接收客户端数据
    int ret=0;
    do
    {
        char buf2[100] = {0};
        ret = recv(c, buf2, 100, 0);

        // 判断前两位，粗浅的判断消息是否为空
        if (buf2[0] != 0 && buf2[1] != 0) {
            for (const auto & user : users) {
                if (user != c) {
                    // 通知其他用户
                    send(user, buf2, 100, 0);
                }
            }
        }

        cout << c << ": " << buf2 << endl;
    } while (ret!=SOCKET_ERROR && ret!=0);

    for (auto i = users.begin(); i != users.end(); i ++ ) {
        if (*i == c) {
            users.erase(i);
            break;
        }
    }

    cout << c << " leaves " << endl;

    char leaveMessage[100] = {0};
    sprintf(leaveMessage,"%llu leaves", c);
    for (const auto & user : users) {
        send(user, leaveMessage, 100, 0);
    }

    return 0;
}
