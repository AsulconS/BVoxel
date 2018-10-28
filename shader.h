#ifndef SHADER_H
#define SHADER_H

#include "transform.h"
#include "camera.h"
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

    enum
    {
        TRANSFORM_U,
        NUM_UNIFORMS
    };

    GLuint program;
    GLuint shaders[NUM_SHADERS];
    GLuint uniforms[NUM_UNIFORMS];

    // Private Functions
    std::string loadShader(const std::string& fileName); // Load the file and return it into a string
    void checkShaderError(GLuint shader, GLenum flag, bool isProgram, const std::string& errorMessage);
    GLuint createShader(const std::string& text, GLenum shaderType);
    
public:
    Shader(const std::string& fileName);
    virtual ~Shader();

    void bind();
    void update(const Transform& transform, const Camera& camera);
};

#endif // SHADER_H
