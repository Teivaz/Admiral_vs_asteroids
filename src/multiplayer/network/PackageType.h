#pragma once

class PackageType
{
public:
    enum Type
    {
        PING = 0,
        GET_CLIENT_INFO = 1,
        GET_STATUS = 2,
        LOBBY_USERS = 3,
        GET_SERVER_INFO = 4,
    };
};

