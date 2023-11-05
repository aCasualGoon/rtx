#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp> 
using namespace glm;

mat4 matrix_from_posrot(const vec3 position, const vec3 rotation)
{
    float sinX = sin(rotation.x), cosX = cos(rotation.x),
          sinY = sin(rotation.y), cosY = cos(rotation.y),
          sinZ = sin(rotation.z), cosZ = cos(rotation.z);
    return mat4(
        cosY * cosZ                     , -cosY * sinZ                     ,  sinY       ,  0.0f,
        sinX * sinY * cosZ + cosX * sinZ,  cosX * cosZ - sinX * sinY * sinZ, -sinX * cosY,  0.0f,
        sinX * sinZ - cosX * sinY * cosZ,  cosX * sinY * sinZ + sinX * cosZ,  cosX * cosY,  0.0f,
        position.x                      ,  position.y                      ,  position.z ,  1.0f
    );
}

const GLfloat vertices[20] = {
//    X      Y     Z     U     V
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left corner
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom right corner
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // Top right corner
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // Top left corner
};
const GLuint indices[6] = { 0, 1, 2, 2, 3, 0 };

// GLuint VAO, VBO, EBO;
void init_quad_data(GLuint &VAO, GLuint &VBO, GLuint &EBO)
{
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

Camera::Camera(EngineContext *context, Shader *shader)
{
    this->context = context;
    this->shader = shader;

    this->transform = matrix_from_posrot(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f,0.0f,0.0f));

    this->view = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    this->clip = vec2(0.0f, 1000.0f);

    this->fov = 90.0f;

    init_quad_data(this->VAO, this->VBO, this->EBO);
    shader->use();
}

void Camera::render()
{
    // Draw the quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers
    SDL_GL_SwapWindow(context->window);
}

// getters & setters
vec3 Camera::get_position()
    { return vec3(this->transform[3][0], this->transform[3][1], this->transform[3][2]); }
void Camera::set_position(vec3 position)
    { this->transform[3][0] = position.x; this->transform[3][1] = position.y; this->transform[3][2] = position.z; }

vec2 Camera::get_clip()
    { return this->clip; }
void Camera::set_clip(vec2 clip)
    { this->clip = clip; }
float Camera::get_clip_near()
    { return this->clip.x; }
void Camera::set_clip_near(float clip_near)
    { this->clip.x = clip_near; }
float Camera::get_clip_far()
    { return this->clip.y; }
void Camera::set_clip_far(float clip_far)
    { this->clip.y = clip_far; }

float Camera::get_fov()
    { return this->fov; }
void Camera::set_fov(float fov)
    { this->fov = fov; }

Camera::~Camera()
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