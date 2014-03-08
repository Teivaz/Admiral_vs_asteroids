#pragma once

#ifdef _WIN32
#define Socket  SOCKET
#define Data    WSADATA
#else // IOS

#endif

class Connection
{
    Connection();
    ~Connection();

    bool                    connectToHost(int portNo, char* ip);
    void                    closeConnection();
    bool                    listenOnPort(int port);

private:
    Socket                  m_socket;
    Data                    m_data;
};
