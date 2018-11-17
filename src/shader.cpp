#include "shader.h"

Shader::Shader(const std::string& fileName)
{
    // HANDLE of the program
    program = glCreateProgram();
    // Creating Shaders and save HANDLEs
    shaders[VERTEX_SHADER] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    // Attaching the Shaders to the program
    for(unsigned int i = 0; i < NUM_SHADERS; ++i)
        glAttachShader(program, shaders[i]);
    
    // Setting the vertex attribute of the program in the index 0 with the variable "position"
    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texCoord");
    glBindAttribLocation(program, 2, "normal");

    // Linking of Program
    glLinkProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed");

    // Validation of Program
    glValidateProgram(program);
    checkShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

    uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; ++i)
    {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(program);
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::update(const Transform& transform, const Camera& camera)
{
    glm::mat4 model = camera.getViewProjection() * transform.getModel();

    glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
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
