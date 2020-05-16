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

    const GLuint SAMPLES{ 8 };

    uint32_t width{ 800 };
    uint32_t height{ 600 };

    GLuint vao{};
    GLuint vbo{};
    core::Shader* program{};

    GLuint fbo{};
    GLuint texColorBuffer{};
    GLuint rbo{};

protected:
    void Init() override
    {
        InitFramebuffer();
        InitBuffers();

        program = new core::Shader("vertex.vert", "fragment.frag");
    }

    void Update(float deltaTime) override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glEnable(GL_DEPTH_TEST);
        glClearColor(COLOR_YELLOW.x, COLOR_YELLOW.y, COLOR_YELLOW.z, COLOR_YELLOW.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);
        program->SetActive(true);

        program->setVec4(SHADER_PROPERTY_COLOR, COLOR_BLUE);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        program->setVec4(SHADER_PROPERTY_COLOR, COLOR_RED);
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    void PostUpdate(float) override
    {
    }

    void Dispose() override
    {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteRenderbuffers(1, &rbo);
        glDeleteTextures(1, &texColorBuffer);
        glDeleteFramebuffers(1, &fbo);

        delete program;
    }

    void SetViewport(uint32_t width, uint32_t height) override
    {
        this->width = width;
        this->height = height;
        glViewport(0, 0, width, height);

        glDeleteRenderbuffers(1, &rbo);
        glDeleteTextures(1, &texColorBuffer);
        glDeleteFramebuffers(1, &fbo);

        InitFramebuffer();
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
    }

    void InitFramebuffer()
    {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        glGenTextures(1, &texColorBuffer);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texColorBuffer);

        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, SAMPLES, GL_RGB, width, height, GL_TRUE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texColorBuffer, 0);


        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);

        glRenderbufferStorageMultisample(GL_RENDERBUFFER, SAMPLES, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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