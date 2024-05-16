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

// ���û��ĶԻ������û� id
void getMessageWithUserName(char*& res, char* buf, unsigned long long int user);

int main() {
    WSADATA wd;
    if(WSAStartup(MAKEWORD(2,2), &wd) != 0)
    {
        cout << "WSAStartup Error:" << WSAGetLastError() << endl;
        return 0;
    }

    // 1. ������ʽ�׽���
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s == INVALID_SOCKET)
    {
        cout << "socket error:" << WSAGetLastError() << endl;
        return 0;
    }

    // 2. �󶨶˿ں�ip
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

    // 3. ����
    listen(s,5);

    thread connectClient([&] () {
        while(true)
        {
            sockaddr_in addrClient{};
            len = sizeof(sockaddr_in);
            // 4.���ܳɹ�������clientͨѶ��Socket
            SOCKET c = accept(s, (SOCKADDR*)&addrClient, &len);
            if(c != INVALID_SOCKET)
            {
                // �����̣߳����Ҵ�����clientͨѶ���׽���
                HANDLE hThread = CreateThread(nullptr, 0, ThreadFun, (LPVOID)c, 0, NULL);
                CloseHandle(hThread); // �رն��̵߳�����
            }
            else {
                break;
            }
        }
    } );

    connectClient.detach();

    // ���߳�ѭ�����տͻ��˵�����

    while (true) {
        string command;
        cin >> command;
        if (command == "exit") {
            break;
        }
    }

    // 6.�رռ����׽���
    closesocket(s);

    // ����win sock2�Ļ���
    WSACleanup();

    return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{
    // 5.��ͻ���ͨѶ�����ͻ��߽�������
    auto c= (SOCKET)lpThreadParameter;

    char buf[100] = {0};
    // ���������������޷�����
    if (users.size() >= 2) {
        sprintf(buf, "There can be only two person!");
        send(c, buf, 100, 0);
        return 0;
    }

    users.emplace_back(c);

    cout << "Welcome " << c << " enter the room!" << endl;


    // ѭ�����տͻ�������
    int ret=0;
    do
    {
        char buf2[100] = {0};
        ret = recv(c, buf2, 100, 0);

        // �ж�ǰ��λ����ǳ���ж���Ϣ�Ƿ�Ϊ��
        if (buf2[0] != 0 && buf2[1] != 0) {
            for (const auto & user : users) {
                if (user != c) {
                    // ֪ͨ�����û�
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
