#ifndef _SOCKET_H_
#define _SOCKET_H_


#include<string>
#include<WinSock2.h>
#include<iostream>

#pragma comment(lib, "ws2_32.lib")


/// @brief 打开网络库
/// @return 成功or失败
bool initSocket();

/// @brief 关闭网络库
/// @return 成功or失败
bool closeSocket();

/// @brief 创建服务器套接字
/// @return 套接字
SOCKET createServerSocket();

/// @brief 创建客户端套接字
/// @return 套接字
SOCKET createClientSocket(const std::string& ip);

/// @brief 错误检查
/// @param msg 错误描述
void checkError(const std::string& msg);

#endif // !_SOCKET_H_

