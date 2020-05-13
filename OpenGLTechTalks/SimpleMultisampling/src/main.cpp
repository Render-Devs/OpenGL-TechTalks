#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Basic.h"
#include "Shader.h"

#include <iostream>
#include <vector>

class DrawElementsBaseRenderer final : public IRenderer
{
private:
    const char* SHADER_PROPERTY_COLOR = "color";

    const float Z_FIRST = 0.0f;
    const float Z_SECOND = 0.1f;

    const glm::vec4 COLOR_YELLOW = glm::vec4(1, 1, 0, 1);
    const glm::vec4 COLOR_BLUE = glm::vec4(0, 0, 1, 1);
    const glm::vec4 COLOR_RED = glm::vec4(1, 0, 0, 1);

    const std::vector<GLfloat> vertices
    {
        -0.5f, -0.5f, Z_FIRST,
         0.0f,  0.5f, Z_FIRST,
         0.5f, -0.5f, Z_FIRST,

        -0.5f,  0.5f, Z_SECOND,
         0.5f,  0.5f, Z_SECOND,
         0.0f, -0.5f, Z_SECOND,
    };

    GLuint vao{};
    GLuint vbo{};
    core::Shader* program{};

protected:
    void Init() override
    {
        InitBuffers();

        program = new core::Shader("vertex.vert", "fragment.frag");
    }

    void Update(float deltaTime) override
    {
        glClearColor(COLOR_YELLOW.x, COLOR_YELLOW.y, COLOR_YELLOW.z, COLOR_YELLOW.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);

        program->SetActive(true);

        program->setVec4(SHADER_PROPERTY_COLOR, COLOR_BLUE);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        program->setVec4(SHADER_PROPERTY_COLOR, COLOR_RED);
        glDrawArrays(GL_TRIANGLES, 3, 6);
    }

    void PostUpdate(float) override
    {
    }

    void Dispose() override
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        delete program;
    }

    void SetViewport(uint32_t width, uint32_t height) override
    {
        glViewport(0, 0, width, height);
    }

private:
    void InitBuffers()
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
    return new App(new DrawElementsBaseRenderer(), WindowData("Uniforms", 800, 600));
}