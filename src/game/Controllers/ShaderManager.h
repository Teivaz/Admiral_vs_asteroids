#pragma once
#include "shaders.h"

MakeShared(Shader);

class ShaderManager : public Singleton<ShaderManager>
{
    typedef std::map<string, ShaderPtr> ShaderMap_t;
public:
    ShaderManager();
    ~ShaderManager();

    void                            loadShader(const string&);
    ShaderProgram                   getShader(const string&);

private:
    ShaderPtr                       _loadShader(const string& name);
    ShaderPtr                       _createShader(const char* vs, const char* fs);

private:
    ShaderMap_t                     m_shaders;
};