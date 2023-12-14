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

Camera::Camera(){}
Camera::Camera(EngineContext *context, Shader *shader)
{
    this->context = context;
    this->shader = shader;

    set_position(0.0f, 0.0f, -5.0f);
    set_rotation(0.0f, 0.0f);
    set_clip(0.1f, 1000.0f);
    set_fov(60.0f);

    init_quad_data(this->VAO, this->VBO, this->EBO);
    shader->use();
}

void Camera::render()
{
    // calculate the cam2world matrix
    mat4 cam2world = inverse(mat4_cast(conjugate(this->rotation)) * translate(mat4(1.0f), -this->position));
    // set the cam2world matrix in the shader
    // this->shader->setMatrix("cam2world", cam2world);
    glUniformMatrix4fv(glGetUniformLocation(this->shader->program, "cam2world"), 1, GL_FALSE, value_ptr(cam2world));

    // calculate near clip data (width, height, distance)
    GLfloat near_clip_width = 2.0f * tan(radians(this->fov / 2.0f)) * this->clip.x;
    GLfloat near_clip_height = near_clip_width / this->context->get_aspect_ratio();
    vec3 near_clip_data = vec3(near_clip_width, near_clip_height, this->clip.x);
    // near_clip_data = vec3(1.0);
    // set the near clip data in the shader
    this->shader->setFloat3("near_clip_data", near_clip_data);
    
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
    // Clamp and normalize yaw
    yaw = fmod(yaw + 180.0f, 360.0f);
    if (yaw < 0) yaw += 360.0f;
    yaw -= 180.0f;

    // Convert to radians
    GLfloat pitchRad = glm::radians(pitch);
    GLfloat yawRad = glm::radians(yaw);

    // Create quaternions
    glm::quat pitchQuat = glm::angleAxis(pitchRad, glm::vec3(1, 0, 0));
    glm::quat yawQuat = glm::angleAxis(yawRad, glm::vec3(0, 1, 0));

    // Combine quaternions
    rotation = yawQuat * pitchQuat;

    // Store the rotation in euler angles
    angular_rotation = vec2(pitch, yaw);
}

vec2 Camera::get_clip()
    { return this->clip; }
void Camera::set_clip(vec2 clip)
    { this->clip = clip; }
GLfloat Camera::get_clip_near()
    { return this->clip.x; }
void Camera::set_clip_near(float clip_near)
    { this->clip.x = clip_near; }
GLfloat Camera::get_clip_far()
    { return this->clip.y; }
void Camera::set_clip_far(float clip_far)
    { this->clip.y = clip_far; }

GLfloat Camera::get_fov()
    { return this->fov; }
void Camera::set_fov(float fov)
    { this->fov = fov; this->fov_rad = radians(fov); }

void Camera::move_by(vec3 delta)
    { this->position += delta; }

void Camera::move_by_local(vec3 delta) 
    { move_by(mat4_cast(this->rotation) * vec4(delta, 1.0f)); }

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