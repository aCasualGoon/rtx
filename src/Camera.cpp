#include "Camera.h"
#include <iostream>
#include <GL/glew.h>

Camera::Camera(EngineContext *context, Shader *shader)
{
    const GLfloat vertices[20] = {
    //    X      Y     Z     U     V
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left corner
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom right corner
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // Top right corner
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // Top left corner
    };
    const GLuint indices[6] = { 0, 1, 2, 2, 3, 0 };

    this->context = context;
    this->shader = shader;

    // Create and bind a Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind a Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);

    // Create and bind an Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    // Vertex coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    // UV coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void Camera::render()
{
    // Activate the shader
    shader->use();

    // Draw the quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers
    SDL_GL_SwapWindow(context->window);
}

void Camera::cleanup()
{
    // Unbind the VAO, VBO, and EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Delete the VAO, VBO, and EBO
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}