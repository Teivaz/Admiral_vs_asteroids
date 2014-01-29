#pragma once
#include "shaders.h"

class Shader;

class ShaderManager : public Singleton<ShaderManager>
{
    typedef std::map<string, Shader*> ShaderMap_t;
public:
    ShaderManager();
    ~ShaderManager();

    void                            loadShader(const string&);
    ShaderProgram                   getShader(const string&);

private:
    Shader*                         _loadShader(const string& name);
    Shader*                         _createShader(const char* vs, const char* fs);
//    void                            _getShader(const string& name, const char* vs, const char* fs, unsigned int* h);


private:
    ShaderMap_t                     m_shaders;
};