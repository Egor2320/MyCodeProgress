#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "Ws2_32.dll")

namespace http
{

    class TcpServer
    {
    public:

        TcpServer(std::string ip_address, int port);
        ~TcpServer();
        void startListen();

    private:
        std::string m_ip_address;
        int m_port;
        SOCKET m_socket;
        SOCKET m_new_socket;
        long m_incomingMessage;
        struct sockaddr_in m_socketAddress;
        int m_socketAddress_len;
        std::string m_serverMessage;
        WSADATA m_wsaData;

        int startServer();
        void closeServer();
        void acceptConnection(SOCKET &new_socket);
        std::string buildResponse();
        void sendResponse();
    };

}