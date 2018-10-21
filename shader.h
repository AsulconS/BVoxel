#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
private:
    enum
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        NUM_SHADERS
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];

    // Private Functions
    std::string loadShader(const std::string& fileName); // Load the file and return it into a string
    void checkShaderError(GLuint shader, GLenum flag, bool isProgram, const std::string& errorMessage);
    GLuint createShader(const std::string& text, GLenum shaderType);
    
public:
    Shader(const std::string& fileName);
    virtual ~Shader();

    void bind();
};

#endif // SHADER_H
