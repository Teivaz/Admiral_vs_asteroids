#include "Precompiled.h"
#include "AppDelegate.h"

char* pszFragShader = "\
    void main (void)\
    {\
    gl_FragColor = vec4(1.0, 1.0, 0.66 ,1.0);\
    }";

char* pszVertShader = "\
    attribute highp vec4	myVertex;\
    uniform mediump mat4	myPMVMatrix;\
    void main(void)\
    {\
    gl_Position = myPMVMatrix * myVertex;\
    }";

GLuint uiProgramObject;


void AppDelegate::Init()
{
    GLuint uiFragShader, uiVertShader;
    //GLuint uiProgramObject;
    uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(uiFragShader, 1, (const char**)&pszFragShader, NULL);
    glCompileShader(uiFragShader);

    GLint bShaderCompiled = 0;
    glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &bShaderCompiled);

    if (!bShaderCompiled)
    {

        // An error happened, first retrieve the length of the log message
        int i32InfoLogLength, i32CharsWritten;
        glGetShaderiv(uiFragShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

        // Allocate enough space for the message and retrieve it
        char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(uiFragShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

        // Displays the error in a dialog box
        MessageBox(window, i32InfoLogLength ? pszInfoLog : (""), ("Failed to compile fragment shader"), MB_OK | MB_ICONEXCLAMATION);
        delete[] pszInfoLog;
    }

    uiVertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(uiVertShader, 1, (const char**)&pszVertShader, NULL);
    glCompileShader(uiVertShader);
    glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &bShaderCompiled);
    if (!bShaderCompiled)
    {

        int i32InfoLogLength, i32CharsWritten;
        glGetShaderiv(uiVertShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
        char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(uiVertShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

        MessageBox(window, i32InfoLogLength ? pszInfoLog : (""), ("Failed to compile vertex shader"), MB_OK | MB_ICONEXCLAMATION);

        delete[] pszInfoLog;
    }
    uiProgramObject = glCreateProgram();
    glAttachShader(uiProgramObject, uiFragShader);
    glAttachShader(uiProgramObject, uiVertShader);
    glBindAttribLocation(uiProgramObject, 0, "myVertex");
    glLinkProgram(uiProgramObject);
    GLint bLinked;
    glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);
    if (!bLinked)
    {
        int i32InfoLogLength, i32CharsWritten;
        glGetProgramiv(uiProgramObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
        char* pszInfoLog = new char[i32InfoLogLength];
        glGetProgramInfoLog(uiProgramObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

        MessageBox(window, i32InfoLogLength ? pszInfoLog : (""), ("Failed to link program"), MB_OK | MB_ICONEXCLAMATION);

        delete[] pszInfoLog;
    }
    glUseProgram(uiProgramObject);
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    GLuint	ui32Vbo;

    GLfloat afVertices[] = { -0.4f, -0.4f, 0.0f, // Position
        0.4f, -0.4f, 0.0f,
        0.0f, 0.4f, 0.0f };

    glGenBuffers(1, &ui32Vbo);

    glBindBuffer(GL_ARRAY_BUFFER, ui32Vbo);
    unsigned int uiSize = 3 * (sizeof(GLfloat)* 3); // Calc afVertices size (3 vertices * 
    glBufferData(GL_ARRAY_BUFFER, uiSize, afVertices, GL_STATIC_DRAW);

}

void AppDelegate::Update(float dt)
{

}

float pfIdentity[] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

void AppDelegate::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int i32Location = glGetUniformLocation(uiProgramObject, "myPMVMatrix");
    glUniformMatrix4fv(i32Location, 1, GL_FALSE, pfIdentity);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    eglSwapBuffers(display, surface);
}
