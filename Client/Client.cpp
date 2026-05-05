#include"../Socket/Socket.h"

#include<thread>

const uint32_t bufferSize = 1024;

void sendThreadFunc(SOCKET serverSock)
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
        if (send(serverSock, message.c_str(), (int)message.size(), 0) == SOCKET_ERROR)
        {
            checkError("send");
        }
    }

}

void recvThreadFunc(SOCKET serverSock)
{
    char recvBuffer[bufferSize] = {};
    while (true)
    {
        if (recv(serverSock, recvBuffer, bufferSize, 0) > 0)
        {
            printf("\n[Server]: %s\n[You]: ", recvBuffer);
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

    SOCKET serverSock = createClientSocket("127.0.0.1");

    if (serverSock != INVALID_SOCKET)
    {
        printf("Connect server successful!\n");
    }

    std::thread sendThread(sendThreadFunc, serverSock);
    std::thread recvThread(recvThreadFunc, serverSock);

    if (sendThread.joinable())
    {
        sendThread.join();
    }
    if (recvThread.joinable())
    {
        recvThread.join();
    }

    closesocket(serverSock);
    closeSocket();
    printf("Client closed\n");

    return 0;
}