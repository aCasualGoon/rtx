#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "EngineContext.h"
#include "Shader.h"
using namespace glm;

/**
 * @brief The Camera class represents a camera in the 3D world.
 * It is responsible for rendering the scene from its point of view.
 */
class Camera {
private:
    EngineContext *context;
    Shader *shader;
    vec3 position;
    vec2 angular_rotation; // rotation as (pitch,yaw) / (along local x axis, along y axis) in degrees [-180,180].
    quat rotation;
    vec2 clip; /** x = near, y = far */
    float fov;
    float fov_rad;
    GLuint VAO, VBO, EBO;
public:
    Camera();
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
    /**
     * @brief Sets the camera's position. 
     * @param x The new x position.
     * @param y The new y position.
     * @param z The new z position. 
     */
    inline void set_position(GLfloat x, GLfloat y, GLfloat z) {set_position(vec3(x,y,z));}

    /** @brief Gets the camera's rotation as (pitch,yaw) in degrees. @return The camera's rotation as (pitch,yaw) in degrees [-180,180]. */
    vec2 get_rotation();
    /** 
     * @brief Sets the camera's rotation as (pitch,yaw) in degrees. 
     * @param pitch The rotation along the local x axis in degrees.
     * @param yaw The rotation along the y axis in degrees.
     */
    void set_rotation(GLfloat pitch, GLfloat yaw);
    /** @brief Sets the camera's rotation as (pitch,yaw) in degrees. @param rotation The new rotation as (pitch,yaw) in degrees [-180,180]. */
    inline void set_rotation(vec2 rotation) { set_rotation(rotation.x,rotation.y); }

    /** @brief Gets the camera's clipping planes. @return The camera's clipping planes (near, far). */
    vec2 get_clip();
    /** @brief Sets the camera's clipping planes. @param clip The new clipping planes (near, far). */
    void set_clip(vec2 clip);
    /**
     * @brief Sets the camera's clipping planes.
     * @param clip_near The new near clipping plane.
     * @param clip_far The new far clipping plane.
     */
    inline void set_clip(float clip_near, float clip_far) {set_clip(vec2(clip_near,clip_far));}
    /** @brief Gets the camera's near clipping plane. @return The camera's near clipping plane. */
    GLfloat get_clip_near();
    /** @brief Sets the camera's near clipping plane. @param clip_near The new near clipping plane. */
    void set_clip_near(float clip_near);
    /** @brief Gets the camera's far clipping plane. @return The camera's far clipping plane. */
    GLfloat get_clip_far();
    /** @brief Sets the camera's far clipping plane. @param clip_far The new far clipping plane. */
    void set_clip_far(float clip_far);

    /** @brief Gets the camera's field of view in degrees. @return The camera's field of view. */
    GLfloat get_fov();
    /** @brief Sets the camera's field of view in degrees. @param fov The new field of view. */
    void set_fov(float fov);

    /** @brief Moves the camera by the specified delta. @param delta The delta to move by. */
    void move_by(vec3 delta);
    /** 
     * @brief Moves the camera by the specified delta.
     * @param x The delta to move by on the x axis.
     * @param y The delta to move by on the y axis.
     * @param z The delta to move by on the z axis.
     */
    inline void move_by(GLfloat dx, GLfloat dy, GLfloat dz) {move_by(vec3(dx,dy,dz));}
    

    /** @brief Rotates the camera by the specified delta. @param delta The delta as (pitch,yaw) in degrees [-180,180]. */
    void rotate_by(vec2 delta);
    /** 
     * @brief Rotates the camera by the specified delta.
     * @param dpitch The delta to rotate by on the local x axis in degrees [-180,180].
     * @param dyaw The delta to rotate by on the y axis in degrees [-180,180].
     */
    inline void rotate_by(GLfloat dpitch, GLfloat dyaw) {rotate_by(vec2(dpitch,dyaw));}
    
    /** 
     * @brief Rotates the camera by the specified delta, clamping it vertically to [-90,+90].
     * @param dpitch The delta to rotate by on the local x axis in degrees [-180,180].
     * @param dyaw The delta to rotate by on the y axis in degrees [-180,180].
     */
    void rotate_by_clamped(GLfloat dpitch, GLfloat dyaw);
    /** @brief Rotates the camera by the specified delta, clamping it vertically to [-90,+90]. @param delta The delta as (pitch,yaw) in degrees [-180,180]. */
    inline void rotate_by_clamped(vec2 delta) { rotate_by_clamped(delta.x, delta.y); }
    /** 
     * @brief Rotates the camera by the specified delta, clamping it vertically to [min,max].
     * @param dpitch The delta to rotate by on the local x axis in degrees [-180,180].
     * @param dyaw The delta to rotate by on the y axis in degrees [-180,180].
     */
    void rotate_by_clamped(GLfloat dpitch, GLfloat dyaw, GLfloat min, GLfloat max);
    /** @brief Rotates the camera by the specified delta, clamping it vertically to [min,max]. @param delta The delta as (pitch,yaw) in degrees [-180,180]. */
    inline void rotate_by_clamped(vec2 delta, GLfloat min, GLfloat max) { rotate_by_clamped(delta.x, delta.y, min, max); }

    /** @brief Renders the scene from the camera's point of view. */
    void render();

    /** @brief Destroys the camera object. */
    ~Camera();
};

#endif//_CAMERA_H