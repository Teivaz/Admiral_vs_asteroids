#include "Precompiled.h"
#include "TextureManager.h"
#include "utils/FileUtils.h"

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{

}

void TextureManager::loadTexture(const string& name)
{
    if (m_textures.find(name) != m_textures.end())
    {
        return;
    }
    _loadTexture(name);
}
Texture TextureManager::_loadTexture(const string& name)
{
    char* pixels = nullptr;
    unsigned int w, h;
    _loadTexture(name, &pixels, &w, &h);
    Texture tex = _attachTexture(pixels, w, h);
    m_textures[name] = tex;
    return tex;
}

Texture TextureManager::getTexture(const string& name)
{
    auto t = m_textures.find(name);
    if (t != m_textures.end())
    {
        return t->second;
    }
    return _loadTexture(name);
}

void TextureManager::_loadTexture(const string& name, char** pixels, unsigned int* w, unsigned int* h)
{
    char* data;
    size_t size;
    FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
    unsigned error = lodepng_decode32((unsigned char**)pixels, w, h, (const unsigned char*)data, size);
    //PLOG("%s", lodepng_error_text(error));
    ASSERT(error == 0);
    delete[] data;
}

Texture TextureManager::_attachTexture(const char* pixels, unsigned int w, unsigned int h)
{
    Texture tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, tex);
    ASSERT(tex);
    return tex;
}
