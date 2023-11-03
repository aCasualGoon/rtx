#include "drawing.h"
#include "EngineContext.h"
#include "Shader.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

void draw(EngineContext *context, Shader *shader) {
    // Activate the shader
    shader->use();

    // Define the vertices for a quad (two triangles)
    GLfloat vertices[] = {
    //    X      Y     Z     U     V
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left corner
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom right corner
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // Top right corner
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // Top left corner
    };

    // Define the indices for the quad (two triangles)
    GLuint indices[] = {
        0, 1, 2,   // First triangle
        2, 3, 0    // Second triangle
    };

    // Create and bind a Vertex Array Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind a Vertex Buffer Object
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and bind an Element Buffer Object
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    // Vertex coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // UV coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Draw the quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind the VAO, VBO, and EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Delete the VAO, VBO, and EBO
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    // Swap the buffers
    SDL_GL_SwapWindow(context->window);
}