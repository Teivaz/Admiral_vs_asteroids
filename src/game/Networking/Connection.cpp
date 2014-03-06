#include "Precompiled.h"
#include "Connection.h"
#include <winsock2.h>

Connection::Connection()
{

    ///if (!sdata)
    {
        char sdata[100] = { 0 };// = new char[10];
        recv(s, sdata, 9, 0);
        PLOG("data: %s\n", sdata);
    }

    char* msg = "HELLO there";
    send(s, msg, strlen(msg), 0);

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
            send(s, msg, strlen(msg), 0);
        }
    }
}

Connection::~Connection()
{

}

SOCKET s;
WSADATA w;

char* sdata = nullptr;

bool connectToHost(int portNo, char* ip)
{
    WSADATA wsdata;
    int error = WSAStartup(0x0202, &wsdata);
    if (error)
    {
        return false;
    }
    if (wsdata.wVersion != 0x0202)
    {
        WSACleanup();
        return false;
    }
    SOCKADDR_IN target;

    target.sin_family = AF_INET;
    target.sin_port = htons(portNo);
    target.sin_addr.s_addr = inet_addr(ip);

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        return false;
    }

    if (connect(s, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

void closeConnection()
{
    if (s)
    {
        closesocket(s);
    }
    WSACleanup();
}

bool listenOnPort(int port)
{
    int error = WSAStartup(0x0202, &w);

    if (error)
    {
        return false;
    }
    if (w.wVersion != 0x0202)
    {
        WSACleanup();
        return false;
    }
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        return false;
    }

    if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        return false;
    }
    error = listen(s, SOMAXCONN);
    return true;
}

