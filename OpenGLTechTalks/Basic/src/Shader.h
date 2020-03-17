#ifndef SHADER
#define SHADER

#include <glad/glad.h>

#include <string>

namespace core
{
    class Shader
    {
    private:
        GLuint m_ID;
    public:
        Shader();

        Shader(const char* vertexPath, const char* fragmentPath);

        ~Shader();

        void SetActive(bool value) const;

        GLuint getID() const;

        void setBool(const std::string& name, bool value) const;

        void setInt(const std::string& name, int value) const;

        void setFloat(const std::string& name, float value) const;

    private:
        static bool checkCompileErrors(GLuint shader, std::string type);
    };    
}

#endif