#include <glad/glad.h>

#include "Basic.h"

#include <iostream>
#include <vector>

class DrawArraysRenderer : public IRenderer
{
private:
    const std::vector<GLfloat> vertices0
    {
        -1.00f, 1.00f, 0.00f,
        0.00f, 1.00f, 0.00f,
        -1.00f, 0.00f, 0.00f
    };

    const std::vector<GLfloat> vertices1
    {
        1.00f, -1.00f, 0.00f,
        0.00f, -1.00f, 0.00f,
        1.00f,  0.00f, 0.00f
    };

    const std::vector<GLfloat> vertices2
    {
        -1.00f, -1.00f, 0.00f,
        -1.00f, -0.50f, 0.00f,
        -0.50f, -1.00f, 0.00f
    };

    const std::vector<GLfloat> vertices3
    {
        1.00f, 1.00f, 0.00f,
        1.00f, 0.50f, 0.00f,
        0.50f, 1.00f, 0.00f
    };

    const std::vector<std::vector<GLfloat>> vertices
    {
        vertices0, vertices1, vertices2, vertices3
    };

    GLuint vao[4]{};
    GLuint vbo[4]{};
    GLuint shaderProgram{};

protected:
    void Init() override
    {
        glGenVertexArrays(4, vao);
        glGenBuffers(4, vbo);

        GenerateData(0);
        GenerateData(1);
        GenerateData(2);
        GenerateData(3);

        shaderProgram = CreateShaderProgram();
    }

    void Update(float deltaTime) override
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(vao[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(vao[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void PostUpdate(float deltaTime) override
    {
    }

    void Dispose() override
    {
        glDeleteVertexArrays(4, vao);
        glDeleteBuffers(4, vbo);
        glDeleteProgram(shaderProgram);
    }

    void SetViewport(uint32_t width, uint32_t height) override
    {
    }

private:
    void GenerateData(unsigned int idx)
    {
        glBindVertexArray(vao[idx]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[idx]);

        glBufferData(GL_ARRAY_BUFFER, vertices[idx].size() * sizeof(GLfloat), vertices[idx].data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

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
    App(IRenderer* render) : Application(render)
    {

    }
};

Application* CreateApplication()
{
    return new App(new DrawArraysRenderer());
}