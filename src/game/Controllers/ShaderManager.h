#pragma once
#include "shaders.h"

class ShaderManager : public Singleton<ShaderManager>
{
    typedef std::map<string, ShaderProgram> ShaderMap_t;
public:
    ShaderManager();
    ~ShaderManager();

    void                            loadShader(const string&);
    ShaderProgram                   getShader(const string&);

private:
    ShaderProgram                   _loadShader(const string& name);
    ShaderProgram                   _createShader(const char* vs, const char* fs);

private:
    ShaderMap_t                     m_shaders;
};