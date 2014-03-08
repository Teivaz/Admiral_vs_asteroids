#include "Precompiled.h"
#include "Connection.h"

#ifdef _WIN32
#else // IOS

#endif



Connection::Connection()
{

    ///if (!sdata)
    {
        char sdata[100] = { 0 };// = new char[10];
        recv(m_socket, sdata, 9, 0);
        PLOG("data: %s\n", sdata);
    }

    char* msg = "HELLO there";
    send(m_socket, msg, strlen(msg), 0);

    int mode = 1;
    if (mode == 1)
    {
        // server
        listenOnPort(1234);
    }
    else if (mode == 2)
    {
        // client
        bool result = connectToHost(1234, "127.0.0.1");
        if (result == true)
        {
            char* msg = "HELLO there";
            send(m_socket, msg, strlen(msg), 0);
        }
    }
}

Connection::~Connection()
{

}

bool Connection::connectToHost(int portNo, char* ip)
{
    int error = WSAStartup(0x0202, &m_data);
    if (error)
    {
        return false;
    }
    if (m_data.wVersion != 0x0202)
    {
        WSACleanup();
        return false;
    }
    SOCKADDR_IN target;

    target.sin_family = AF_INET;
    target.sin_port = htons(portNo);
    target.sin_addr.s_addr = inet_addr(ip);

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

    if (connect(m_socket, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

void Connection::closeConnection()
{
    if (m_socket)
    {
        closesocket(m_socket);
    }
    WSACleanup();
}

bool Connection::listenOnPort(int port)
{
    int error = WSAStartup(0x0202, &m_data);

    if (error)
    {
        return false;
    }
    if (m_data.wVersion != 0x0202)
    {
        WSACleanup();
        return false;
    }
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

    if (bind(m_socket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        return false;
    }
    error = listen(m_socket, SOMAXCONN);
    return true;
}

