#include "GLFWsrc/RendererGLFW.h"
#include "CoreWindow.h"
#include "Renderer/Image.h"
#include "Renderer/RendererImplementation.h"
#include "glad/glad.h"

namespace Core {
    RendererGLFW::~RendererGLFW() {};
    RendererGLFW::RendererGLFW() {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RendererGLFW::Draw(Image &pic, int xCoord, int yCoord) {

      float vertices[] = {
          xCoord * 1.0f,
          yCoord * 1.0f,
          0.0f,
          0.0f, // bottom left
          (xCoord + pic.GetWidth()) * 1.0f,
          yCoord * 1.0f,
          1.0f,
          0.0f, // bottom right
          xCoord * 1.0f,
          (yCoord + pic.GetHeight()) * 1.0f,
          0.0f,
          1.0f, // top left
          (xCoord + pic.GetWidth()) * 1.0f,
          (yCoord + pic.GetHeight()) * 1.0f,
          1.0f,
          1.0f // top right
      };

      unsigned int indices[] = {
          0, 1, 2, // first triangle
          1, 2, 3  // second triangle
      };

      unsigned int VAO = 0;
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

      unsigned int VBO;
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                            (void *)(2 * sizeof(float)));
      glEnableVertexAttribArray(1);

      unsigned int EBO = 0;
      glGenBuffers(1, &EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                   GL_STATIC_DRAW);

      mDefaultShaders.Bind();
      mDefaultShaders.SetIntegerUniform("ScreenDimensions",
                                        {CoreWindow::GetWindow()->GetWidth(),
                                         CoreWindow::GetWindow()->GetHeight()});

      pic.Bind(); // CRITICAL: Bind texture before drawing

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RendererGLFW::Draw(Image &pic, int xCoord, int yCoord, Shader &shaders) {
      float vertices[] = {
          xCoord * 1.0f,
          yCoord * 1.0f,
          0.0f,
          0.0f, // bottom left
          (xCoord + pic.GetWidth()) * 1.0f,
          yCoord * 1.0f,
          1.0f,
          0.0f, // bottom right
          xCoord * 1.0f,
          (yCoord + pic.GetHeight()) * 1.0f,
          0.0f,
          1.0f, // top left
          (xCoord + pic.GetWidth()) * 1.0f,
          (yCoord + pic.GetHeight()) * 1.0f,
          1.0f,
          1.0f // top right
      };

      unsigned int indices[] = {
          0, 1, 2, // first triangle
          1, 2, 3  // second triangle
      };

      unsigned int VAO = 0;
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

      unsigned int VBO;
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                            (void *)(2 * sizeof(float)));
      glEnableVertexAttribArray(1);

      unsigned int EBO = 0;
      glGenBuffers(1, &EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                   GL_STATIC_DRAW);

      shaders.Bind();
      shaders.SetIntegerUniform("ScreenDimensions",
                                {CoreWindow::GetWindow()->GetWidth(),
                                 CoreWindow::GetWindow()->GetHeight()});

      pic.Bind();

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RendererGLFW::ClearScreen() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };

    void RendererGLFW::ClearScreen(std::vector<float>& clearColor) {
        assert (clearColor.size() == 3);
        glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };
} // namespace Core

