#ifndef SHADER
#define SHADER

#include <glad/glad.h>

#include <string>

namespace core
{
    class Shader
    {
    private:
        unsigned int m_ID;
    public:
        Shader();

        Shader(const char* vertexPath, const char* fragmentPath);

        ~Shader();

        void activate();

        void deActivate();

        unsigned int getID();

        void setBool(const std::string& name, bool value) const;

        void setInt(const std::string& name, int value) const;

        void setFloat(const std::string& name, float value) const;

        void setFloat4(const std::string& name, float x, float y, float z, float w) const;

    private:
        void checkCompileErrors(GLuint shader, std::string type);
    };    
}

#endif