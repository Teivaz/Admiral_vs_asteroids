#include "Precompiled.h"
#include "ShaderManager.h"
#include "ShaderAttributes.h"
#include "utils/FileUtils.h"

#ifndef VERBOSE_SHADER_DEBUG
#define VERBOSE_SHADER_DEBUG 0
#endif

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
    for (auto p : m_shaders)
    {
        glDeleteProgram(p.second);
    }
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
        return t->second;
    }
    return _loadShader(name);
}

ShaderProgram ShaderManager::_loadShader(const string& name)
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
    ShaderProgram shader = _createShader(vs.asCString(), fs.asCString());
    m_shaders[name] = shader;
    return shader;
}

ShaderProgram ShaderManager::_createShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    VertexShader vs = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader fs = glCreateShader(GL_FRAGMENT_SHADER);

#ifdef _WIN32
	glShaderSource(vs, 1, &vertexShaderSource, NULL);
#else // IOS
	string vertexShaderSourceString(string("#define IOS\n") + vertexShaderSource);
	const char* vertexShaderSourceCstring = vertexShaderSourceString.c_str();
	glShaderSource(vs, 1, &vertexShaderSourceCstring, NULL);
#endif
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

    glBindAttribLocation(program, Attributes::VERTEX_COORDINATES, "a_position");
    glBindAttribLocation(program, Attributes::VERTEX_NORMALS, "a_normals");
    glBindAttribLocation(program, Attributes::TEXTURE_COORDINATES, "a_texturePosition");
    glBindAttribLocation(program, Attributes::TEXTURE2_COORDINATES, "a_texture2Position");
    glBindAttribLocation(program, Attributes::TEXTURE3_COORDINATES, "a_texture3Position");

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
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
