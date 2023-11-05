#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;
#include "EngineContext.h"
#include "Shader.h"

/**
 * @brief The Camera class represents a camera in the 3D world.
 * 
 * It is responsible for rendering the scene from its point of view.
 */
class Camera {
private:
    EngineContext *context;
    Shader *shader;
    mat4 transform;
    mat4 view;
    vec2 clip; /** x = near, y = far */
    float fov;
    GLuint VAO, VBO, EBO;
public:
    /**
     * @brief Constructs a new Camera object.
     * @param context The engine context.
     * @param shader The shader used for rendering the scene.
     */
    Camera(EngineContext *context,Shader *shader);

    /** @brief Gets the camera's position. @return The camera's position. */
    vec3 get_position();
    /** @brief Sets the camera's position. @param position The new position. */
    void set_position(vec3 position);

    /** @brief Gets the camera's clipping planes. @return The camera's clipping planes (near, far). */
    vec2 get_clip();
    /** @brief Sets the camera's clipping planes. @param clip The new clipping planes (near, far). */
    void set_clip(vec2 clip);
    /** @brief Gets the camera's near clipping plane. @return The camera's near clipping plane. */
    float get_clip_near();
    /** @brief Sets the camera's near clipping plane. @param clip_near The new near clipping plane. */
    void set_clip_near(float clip_near);
    /** @brief Gets the camera's far clipping plane. @return The camera's far clipping plane. */
    float get_clip_far();
    /** @brief Sets the camera's far clipping plane. @param clip_far The new far clipping plane. */
    void set_clip_far(float clip_far);

    /** @brief Gets the camera's field of view. @return The camera's field of view. */
    float get_fov();
    /** @brief Sets the camera's field of view. @param fov The new field of view. */
    void set_fov(float fov);

    /** @brief Renders the scene from the camera's point of view. */
    void render();

    /** @brief Destroys the camera object. */
    ~Camera();

    /** @brief Calls the object's destructor. */
    void destruct() { this->~Camera(); }
};

#endif//_CAMERA_H