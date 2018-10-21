#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName)
{
    // HANDLE of the program
    m_program = glCreateProgram();
    // Creating Shaders and save HANDLEs
    m_shaders[VERTEX_SHADER] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[FRAGMENT_SHADER] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    // Attaching the Shaders to the program
    for(unsigned int i = 0; i < NUM_SHADERS; ++i)
        glAttachShader(m_program, m_shaders[i]);
    
    // Setting the vertex attribute of the program in the index 0 with the variable "position"
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");

    // Linking of Program
    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed");

    // Validation of Program
    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
}

Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; ++i)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}

void Shader::bind()
{
    glUseProgram(m_program);
}

// Create a Shader and return its HANDLE
GLuint Shader::createShader(const std::string& text, GLenum shaderType)
{
    // Creating shader HANDLE with the shaderType
    GLuint shader = glCreateShader(shaderType);

    // If 0, it's an error and we print out in cerr
    if(shader == 0)
        std::cerr << "Error: Shader creation failed" << std::endl;
    
    // Variables with the content passed in text
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringsLengths[1];

    // Initializating them
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLengths[0] = text.length();

    // Setting the Sources to the shader
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
    glCompileShader(shader);

    // Checking for error
    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

    // And return the shader
    return shader;
}

// Load the file and return it into a string
std::string Shader::loadShader(const std::string& fileName)
{
    std::ifstream file; // File variable
    file.open((fileName).c_str()); // File is opened

    std::string output; // Here we will save the file content
    std::string line; // Temporary line
    
    // The file is read and saved into ouput
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line); // Getting line in line
            output.append(line + '\n'); // Appending into output with '\n'
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::checkShaderError(GLuint shader, GLenum flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    // Checking the error with the FLAG (Parameter)
    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);
    
    // If error, save the info log into error and print out in cerr
    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
