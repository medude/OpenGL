#ifndef SHADER_HPP
#define SHADER_HPP

#include <sstream>
#include <fstream>

#include "includes.hpp"

class Shader {
public:
    unsigned int ID;
    
    Shader(const char* vertexPath, const char* fragmentPath);
    
    void use();
    void setFloat(const std::string &name, float value) const;
    void setInt(const std::string &name, int value) const;
    void setBool(const std::string &name, bool value) const;
    void set4f(const std::string &name, float valueX, float valueY, float valueZ, float valueW) const;
private:
    int createShader(GLuint shaderType, const char *source);
    int createShaderProgram(int vertexShader, int fragmentShader);
};

#endif
