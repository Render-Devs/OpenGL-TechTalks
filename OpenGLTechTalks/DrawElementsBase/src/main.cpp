#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Basic.h"
#include "Shader.h"

#include <iostream>
#include <vector>

class DrawElementsBaseRenderer final : public IRenderer
{
private:
    const glm::vec4 COLOR_BLUE { 0.0f, 0.51f, 0.82f, 1.0f };
    const glm::vec4 COLOR_YELLOW { 1.0f, 0.82f, 0.0f, 1.0f };
    const char* SHADER_PROPERTY_COLOR = "color";

    const std::vector<GLfloat> vertices
    {
        -0.63f,  0.00f, 0.0f,
        -0.63f,  0.50f, 0.0f,
         0.63f,  0.50f, 0.0f,
         0.63f,  0.00f, 0.0f,

        -0.63f, -0.50f, 0.0f,
        -0.63f,  0.00f, 0.0f,
         0.63f,  0.00f, 0.0f,
         0.63f, -0.50f, 0.0f
    };

    const std::vector<GLuint> indices
    {
        0, 1, 2,
        2, 3, 0
    };

    GLuint vao{};
    GLuint vbo{};
    GLuint ebo{};
    core::Shader* program{};

protected:
    void Init() override
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        program = new core::Shader("vertex.vert", "fragment.frag");
    }

    void Update(float) override
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);

        program->SetActive(true);

        program->setVec4(SHADER_PROPERTY_COLOR, COLOR_BLUE);
        glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 0);

        program->setVec4(SHADER_PROPERTY_COLOR, COLOR_YELLOW);
        glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 4);
    }

    void PostUpdate(float) override
    {
    }

    void Dispose() override
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        delete program;
    }

    void SetViewport(uint32_t width, uint32_t height) override
    {
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
    return new App(new DrawElementsBaseRenderer(), WindowData("glDrawElementsBaseVertex", 800, 600));
}