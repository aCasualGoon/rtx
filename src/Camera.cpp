#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

const GLfloat vertices[20] = {
//    X      Y     Z     U     V
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left corner
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom right corner
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // Top right corner
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // Top left corner
};
const GLuint indices[6] = { 0, 1, 2, 2, 3, 0 };

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

Camera::Camera(){}
Camera::Camera(EngineContext *context, Shader *shader)
{
    this->context = context;
    this->shader = shader;

    set_position(0.0f, 0.0f, -5.0f);
    set_rotation(0.0f, 0.0f);
    set_fov(60.0f);

    init_quad_data(VAO, VBO, EBO);
    shader->use();
}

void Camera::render() {
    // calculate & set the cam2world matrix
    shader->setMatrix("cam2world", inverse(mat4_cast(conjugate(rotation)) * mat4(1,0,0,0,0,1,0,0,0,0,1,0,-position.x,-position.y,-position.z,1)));
    
    // calculate & set the near clip data (width, height)
    // we use an imaginary clip plane at distance 1.0 to calculate the ray position and direction 
    // we don't actually clip
    GLfloat near_clip_width = 2.0f * tan(radians(fov / 2.0f));
    GLfloat near_clip_height = near_clip_width / context->get_aspect_ratio();
    shader->setFloat2("near_clip_data", vec2(near_clip_width, near_clip_height));

    // Draw the quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers
    SDL_GL_SwapWindow(context->window);
}

vec3 Camera::get_position()
    { return this->position; }
void Camera::set_position(vec3 position)
    { this->position = position; }

vec2 Camera::get_rotation()
    { return angular_rotation; }

void Camera::set_rotation(GLfloat pitch, GLfloat yaw) {
    angular_rotation = vec2(pitch, yaw);
    rotation = angleAxis(radians(yaw), glm::vec3(0, 1, 0)) * angleAxis(radians(pitch), glm::vec3(1, 0, 0));
}

GLfloat Camera::get_fov()
    { return this->fov; }
void Camera::set_fov(float fov)
    { this->fov = fov; this->fov_rad = radians(fov); }

void Camera::move_by(vec3 delta)
    { this->position += delta; }

void Camera::move_by_local(vec3 delta)
    { move_by((vec3)(mat4_cast(this->rotation) * vec4(delta.x, 0, delta.z, 1.0f)) + vec3(0,delta.y,0)); }

void Camera::rotate_by(vec2 delta)
    { set_rotation(get_rotation() + delta); }

void Camera::rotate_by_clamped(GLfloat dpitch, GLfloat dyaw) 
    { set_rotation(clamp(angular_rotation.x + dpitch, -90.0f, 90.0f), angular_rotation.y + dyaw); }
void Camera::rotate_by_clamped(GLfloat dpitch, GLfloat dyaw, GLfloat min, GLfloat max) 
    { set_rotation(clamp(angular_rotation.x + dpitch, min, max), angular_rotation.y + dyaw); }

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