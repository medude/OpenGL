#include <fstream>

#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vSourceStr;
    std::string fSourceStr;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vSourceStr = vShaderStream.str();
        fSourceStr = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR: File Not Successfully Read" << std::endl;
    }
    
    const char* vShaderSrc = vSourceStr.c_str();
    const char* fShaderSrc = fSourceStr.c_str();
    
    unsigned int vert = createShader(GL_VERTEX_SHADER, vShaderSrc);
    unsigned int frag = createShader(GL_FRAGMENT_SHADER, fShaderSrc);
    ID = createShaderProgram(vert, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::use()
{
    glUseProgram(ID);
}

int Shader::createShader(GLuint shaderType, const char *shaderSource)
{
    int shader = glCreateShader(shaderType);
    
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR: Shader Compilation Failed\n" << infoLog << std::endl;
    }
    
    return shader;
}

int Shader::createShaderProgram(int vertexShader, int fragmentShader)
{
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Shader Linking Failed\n" << infoLog << std::endl;
    }
    
    return shaderProgram;
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::set4f(const std::string &name, float valueX, float valueY, float valueZ, float valueW) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), valueZ, valueY, valueZ, valueW);
}