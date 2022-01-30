#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class ShaderManager
{
public:
    // the program ID
    unsigned int ID { 0 };

    ShaderManager(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void checkCompileErrors(GLuint shader, std::string type);

    unsigned int getShaderProgram() { return ID; }
};

