#include <glad/glad.h>

#include "Basic.h"

#include <iostream>
#include <vector>

class DrawElementsRenderer final : public IRenderer
{
private:
    const std::vector<GLfloat> vertices0
    {
        -1.00f,  1.00f, 0.00f,
        -0.25f,  1.00f, 0.00f,
        -0.25f,  0.00f, 0.00f,
        -1.00f,  0.00f, 0.00f,

         1.00f, -1.00f, 0.00f,
         0.25f, -1.00f, 0.00f,
         0.25f,  0.00f, 0.00f,
         1.00f,  0.00f, 0.00f,

         1.00f,  1.00f, 0.00f,
         0.25f,  1.00f, 0.00f,
         0.25f,  0.00f, 0.00f,
         1.00f,  0.00f, 0.00f,

        -1.00f, -1.00f, 0.00f,
        -0.25f, -1.00f, 0.00f,
        -0.25f,  0.00f, 0.00f,
        -1.00f,  0.00f, 0.00f,
    };

    const std::vector<GLuint> indices_0
    {
        0, 1, 2,
        2, 3, 0
    };

    const std::vector<GLuint> indices_1
    {
        7, 4, 5
    };

    const std::vector<GLuint> indices_2
    {
        8,  9,  10,
        10, 11, 8
    };

    const std::vector<GLuint> indices_3
    {
        15, 12, 13
    };

    GLuint vao{};
    GLuint vbo{};
    GLuint ebo[4]{};
    GLuint shaderProgram{};

protected:
    void Init() override
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(4, ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices0.size() * sizeof(GLfloat), vertices0.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_0.size() * sizeof(GLuint), indices_0.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_1.size() * sizeof(GLuint), indices_1.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_2.size() * sizeof(GLuint), indices_2.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[3]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_3.size() * sizeof(GLuint), indices_3.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        shaderProgram = CreateShaderProgram();
    }

    void Update(float) override
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[3]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void PostUpdate(float) override
    {
    }

    void Dispose() override
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(4, ebo);
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
    App(IRenderer* render) : Application(render)
    {

    }
};

Application* CreateApplication()
{
    return new App(new DrawElementsRenderer());
}