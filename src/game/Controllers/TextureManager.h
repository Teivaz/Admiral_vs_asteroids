#pragma once

class TextureManager : public Singleton<TextureManager>
{
    typedef std::map<string, Texture> TexMap_t;

public:
    TextureManager();
    ~TextureManager();

    void                            loadTexture(const string& name);
    Texture                         getTexture(const string& name);

private:
    Texture                         _loadTexture(const string& name);
    Texture                         _getTexture(const string& name);
    void                            _loadTexture(const string& name, char** pixels, unsigned int* w, unsigned int* h);
    Texture                         _attachTexture(const char* pixels, unsigned int w, unsigned int h);

private:
    TexMap_t                        m_textures;

};

