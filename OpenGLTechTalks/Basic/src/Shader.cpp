#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>

namespace core
{
    Shader::Shader() : m_ID{}
    {
    }

    Shader::Shader(const char* vertexPath, const char* fragmentPath) : Shader()
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode = readShader(vertexPath);
        std::string fragmentCode = readShader(fragmentPath);

        // 2. compile shaders

        GLuint vertex = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);

        if (!checkCompileErrors(vertex, "VERTEX"))
        {
            glDeleteShader(vertex);
            return;
        };

        GLuint fragment = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

        if (!checkCompileErrors(fragment, "FRAGMENT"))
        {
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return;
        }

        GLuint programShaders[] = { vertex,fragment };

        compileProgram(programShaders, sizeof(programShaders) / sizeof(programShaders[0]), false);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

	Shader::Shader(const char* shaderPath, GLenum shaderType, bool explicitGeneration = true)
	{
        if (explicitGeneration)
        {
            std::string shaderCode = readShader(shaderPath);
            GLuint shaderPart = compileShader(shaderCode.c_str(), shaderType);
            compileProgram(&shaderPart, 1, true);
        }
        else
        {
            std::string shaderCode = readShader(shaderPath);
            const GLchar* source = shaderCode.c_str();
            m_ID = glCreateShaderProgramv(shaderType, 1, &source);
        }

	}

    Shader::~Shader()
    {
        if (m_ID == 0) return;

        glDeleteProgram(m_ID);
    }

    void Shader::SetActive(bool value) const
    {
        if (value)
        {
            glUseProgram(m_ID);
        }
        else
        {
            glUseProgram(0);
        }
    }

    GLuint Shader::getID() const
    {
        return m_ID;
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    bool Shader::checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                return false;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                return false;
            }
        }

        return true;
    }

    std::string Shader::readShader(const char* path) const
    {
        std::ifstream shaderFile;
        std::string shaderCode;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(path);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderCode = shaderStream.str();
        }
        catch(const std::ifstream::failure&)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << path << std::endl;
        }

        return shaderCode.c_str();
    }

    GLuint Shader::compileShader(const char* shader, GLenum shaderType)
    {
        GLuint shaderObj = glCreateShader(shaderType);
        glShaderSource(shaderObj, 1, &shader, nullptr);
        glCompileShader(shaderObj);

        return shaderObj;
    }

    void Shader::compileProgram(GLuint* shaders, size_t amount, bool separated)
    {
        m_ID = glCreateProgram();

        for (size_t index = 0; index < amount; index++)
        {
            glAttachShader(m_ID, shaders[index]);
        }

        if (separated)
        {
            glProgramParameteri(m_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);
        }

        glLinkProgram(m_ID);

        if (!checkCompileErrors(m_ID, "PROGRAM"))
        {
            glDeleteProgram(m_ID);
        }
    }
}
