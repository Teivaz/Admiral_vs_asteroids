#include "Precompiled.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "utils/FileUtils.h"

#ifndef VERBOSE_SHADER_DEBUG
#define VERBOSE_SHADER_DEBUG 1
#endif

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::loadShader(const string& name)
{
    if (m_shaders.find(name) != m_shaders.end())
    {
        return;
    }
    _loadShader(name);
}

ShaderProgram ShaderManager::getShader(const string& name)
{
    auto t = m_shaders.find(name);
    if (t != m_shaders.end())
    {
        return t->second->program;
    }
    return _loadShader(name)->program;
}

ShaderPtr ShaderManager::_loadShader(const string& name)
{
    char* data;
    size_t size;
    FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
    ASSERT(data && "Error opening shader file");
    Json::Reader reader;
    Json::Value root;
    bool result = reader.parse(data, data + size, root, false);
    ASSERT(result && "Error parsing shader file");
    delete[] data;
    Json::Value vs = root.get("VertexShader", Json::Value(""));
    Json::Value fs = root.get("FragmentShader", Json::Value(""));
    ShaderPtr shader = _createShader(vs.asCString(), fs.asCString());
    m_shaders[name] = shader;
    return shader;
}

ShaderPtr ShaderManager::_createShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    VertexShader vs = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    GLint status = 0;

    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    ASSERT(status && "Error compiling vertex shader.");
#if VERBOSE_SHADER_DEBUG
    {
        GLint infoLen = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLen);
        char* infoLog = new char[infoLen];
        glGetShaderInfoLog(vs, infoLen, NULL, infoLog);
        PLOG("Compiling shader message: %s\n", infoLog);
        delete[] infoLog;
    }
#endif

    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    ASSERT(status && "Error compiling fragment shader.");
#if VERBOSE_SHADER_DEBUG
    {
        GLint infoLen = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infoLen);
        char* infoLog = new char[infoLen];
        glGetShaderInfoLog(fs, infoLen, NULL, infoLog);
        PLOG("Compiling shader message: %s\n", infoLog);
        delete[] infoLog;
    }
#endif

    ShaderProgram program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    ASSERT(status && "Error compiling vertex shader.");
#if VERBOSE_SHADER_DEBUG
    {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        char* infoLog = new char[infoLen];
        glGetShaderInfoLog(fs, infoLen, NULL, infoLog);
        PLOG("Linking shader program message: %s\n", infoLog);
        delete[] infoLog;
    }
#endif
    ShaderPtr shader = ShaderPtr(new Shader(vs, fs, program));
    return shader;
}
