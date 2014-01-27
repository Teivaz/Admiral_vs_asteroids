#pragma once
class Shader;

class ShaderManager : public Singleton<ShaderManager>
{
    typedef std::map<string, Shader*> ShaderMap_t;
public:
    ShaderManager();
    ~ShaderManager();

private:
    ShaderMap_t                     m_shaders;
};