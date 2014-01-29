#pragma once

class Shader
{
public:
    Shader(VertexShader vs, FragmentShader fs, ShaderProgram sp)
        : vertex(vs)
        , fragment(fs)
        , program(sp)
    {}

    const VertexShader          vertex;
    const FragmentShader        fragment;
    const ShaderProgram         program;

private:
    Shader& operator=(const Shader&)
    {
        return *this;
    }
};