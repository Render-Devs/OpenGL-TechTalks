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
    const char* SHADER_PROPERTY_X_OFFSET = "xOffset";
    const char* SHADER_PROPERTY_Y_OFFSET = "yOffset";

    const float X_BOUNDS = 0.75f;
    const float Y_BOUNDS = 0.75f;

    const std::vector<GLfloat> vertices
    {
        -0.25f, -0.25f, 0.0f,
        -0.25f,  0.25f, 0.0f,
         0.25f,  0.25f, 0.0f,
         0.25f, -0.25f, 0.0f
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

    float xOffset{ 0.0f };
    float yOffset{ 0.0f };
    glm::vec4 color{};

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

    void Update(float deltaTime) override
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);

        program->SetActive(true);

        xOffset = float(sin(glfwGetTime()) * X_BOUNDS);
        yOffset = float(cos(glfwGetTime()) * Y_BOUNDS);
        color.x = (float(sin(glfwGetTime())) + 1) / 2;
        color.y = (float(cos(glfwGetTime())) + 1) / 2;
        color.z = color.x + color.y;
        
        program->setFloat(SHADER_PROPERTY_X_OFFSET, xOffset);
        program->setFloat(SHADER_PROPERTY_Y_OFFSET, yOffset);
        program->setVec4(SHADER_PROPERTY_COLOR, color);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    return new App(new DrawElementsBaseRenderer(), WindowData("Uniforms", 800, 600));
}