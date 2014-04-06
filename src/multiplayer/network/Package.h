#pragma once

#include "PackageType.h"

class Package
{
public:
    Package();
    ~Package();

    static Package* create(PackageType::Type, const vector<char>& payload);
    static Package* create(const vector<char>& header, const vector<char>& payload);
    static Package* create(const vector<char>& rawMessage);

    bool isValid() const;

private:
    PackageType::Type       m_type = PackageType::PING;
    vector<char>            m_header;
    vector<char>            m_payload;


};
