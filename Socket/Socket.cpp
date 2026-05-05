#include<stdio.h>
#include<ws2tcpip.h>


#include"Socket.h"


bool initSocket()
{
    WSADATA wsadData;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsadData))
    {
        checkError("WSAStartup");
        return false;
    }
    return true;
}

bool closeSocket()
{
    if (0 != WSACleanup())
    {
        checkError("WSACleanup");
        return false;
    }
    return true;
}

SOCKET createServerSocket()
{
    //af 协议族 ipv4 ipv6
    //type 传输协议类型 流式套接字 数据包套接字
    //protocol 使用具体的传输协议 TCP UDP
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        checkError("socket");
        return INVALID_SOCKET;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);//网络和计算机大小端存储区别
    addr.sin_addr.S_un.S_addr = ADDR_ANY; //inet_addr("127.0.0.1");
    //绑定ip地址和端口号
    if (SOCKET_ERROR == bind(s, (sockaddr*)&addr, sizeof(addr)))
    {
        checkError("bind");
        return 0;
    }

    //监听
    listen(s, 10);

    printf("server socket create successful!\n");

    return s;
}

SOCKET createClientSocket(const std::string& ip)
{
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        checkError("socket");
        return INVALID_SOCKET;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr) != 1)
    {
        checkError("inet_pton");
        return 0;
    }

    //请求链接服务器
    if (connect(s, (sockaddr*)&addr, sizeof(addr)) == INVALID_SOCKET)
    {
        checkError("connect");
        return 0;
    }

    printf("client socket create successful!\n");
    return s;
}

void checkError(const std::string& msg)
{
    printf("[line:%d], %s falied, errCode = %d", __LINE__, msg.c_str(), WSAGetLastError());
}
