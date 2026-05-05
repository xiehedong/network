#include"../Socket/Socket.h"
#include<thread>


const uint32_t bufferSize = 1024;

void sendThreadFunc(SOCKET clientSock)
{
    std::string message;
    while (true)
    {
        std::cout << "[You]: ";
        std::getline(std::cin, message);
        if (message == "quit")
        {
            std::cout << "Quiting..." << std::endl;
            break;
        }
        if (send(clientSock, message.c_str(), (int)message.size(), 0) == SOCKET_ERROR)
        {
            checkError("send");
        }
    }

}

void recvThreadFunc(SOCKET clientSock)
{
    char recvBuffer[bufferSize] = {};
    while (true)
    {
        if (recv(clientSock, recvBuffer, bufferSize, 0) > 0)
        {
            printf("\n[Client]: %s\n[You]: ", recvBuffer);
        }
        else
        {
            break;
        }

        memset(recvBuffer, 0, bufferSize);
    }
}

int main()
{
    initSocket();
    SOCKET serverSock = createServerSocket();

    printf("Waiting client connect...\n");

    //阻塞等待接收客户端的链接请求
    SOCKET clientSock = accept(serverSock, nullptr, nullptr);
    if (clientSock == INVALID_SOCKET)
    {
        checkError("accept");
    }

    printf("Client connect successful!\n");

    std::thread sendThread(sendThreadFunc, clientSock);
    std::thread recvThread(recvThreadFunc, clientSock);

    if (sendThread.joinable())
    {
        sendThread.join();
    }
    if (recvThread.joinable())
    {
        recvThread.join();
    }

    closesocket(clientSock);
    closesocket(serverSock);
    closeSocket();

    printf("Server closed\n");

    return 0;
}