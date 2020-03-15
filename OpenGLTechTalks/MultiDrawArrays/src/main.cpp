#include <glad/glad.h>

#include "Basic.h"

#include <iostream>
#include <vector>

class MultiDrawArraysRenderer final : public IRenderer
{
private:
    const std::vector<GLfloat> vertices
    {
        -1.00f, 1.00f, 0.00f,
         0.00f, 1.00f, 0.00f,
        -1.00f, 0.00f, 0.00f,

         1.00f, -1.00f, 0.00f,
         0.00f, -1.00f, 0.00f,
         1.00f,  0.00f, 0.00f,

        -1.00f, -1.00f, 0.00f,
        -1.00f, -0.50f, 0.00f,
        -0.50f, -1.00f, 0.00f,

         1.00f,  1.00f, 0.00f,
         1.00f,  0.50f, 0.00f,
         0.50f,  1.00f, 0.00f
    };

    GLint     first[4]{ 0, 3, 6, 9 };
    GLint     count[4]{ 3, 3, 3, 3 };
    GLuint    numObjects{ 4 };
    GLuint    vao{};
    GLuint    vbo{};
    GLuint    shaderProgram{};

protected:
    void Init() override
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        shaderProgram = CreateShaderProgram();
    }

    void Update(float) override
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vao);
        glMultiDrawArrays(GL_TRIANGLES, first, count, numObjects);
    }

    void PostUpdate(float) override
    {
    }

    void Dispose() override
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteProgram(shaderProgram);
    }

    void SetViewport(uint32_t width, uint32_t height) override
    {
    }

private:
    static GLuint CreateShaderProgram()
    {
        static const char* vs_source[] =
        {
            "#version 330 core                                                 \n"
            "layout (location = 0) in vec3 aPos;                               \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    gl_Position = vec4(aPos, 1.0);                                \n"
            "}                                                                 \n"
        };

        static const char* fs_source[] =
        {
            "#version 330 core                                                 \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(0.95, 0.55, 0.0, 1.0);                           \n"
            "}                                                                 \n"
        };

        GLuint vertex, fragment, program;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, vs_source, nullptr);
        glCompileShader(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, fs_source, nullptr);
        glCompileShader(fragment);

        program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }
};

class App : public Application
{
public:
    App(IRenderer* render, const WindowData& windowData) : Application(render, windowData)
    {

    }
};

Application* CreateApplication()
{
    return new App(new MultiDrawArraysRenderer(), WindowData("glMultiDrawArrays", 800, 600));
}