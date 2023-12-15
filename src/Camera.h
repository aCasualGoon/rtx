#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "EngineContext.h"
#include "Shader.h"
using namespace glm;

/**
 * The Camera class represents a camera in the 3D world.
 * It is responsible for rendering the scene from its point of view.
 */
class Camera {
private:
    EngineContext *context;
    Shader *shader;
    vec3 position;
    vec2 angular_rotation; // rotation as (pitch,yaw) / (along local x axis, along y axis) in degrees [-180,180].
    quat rotation;
    float fov;
    float fov_rad;
    GLuint VAO, VBO, EBO;
public:
    Camera();
    /**
     * Constructs a new Camera object.
     * @param context The engine context.
     * @param shader The shader used for rendering the scene.
     */
    Camera(EngineContext *context,Shader *shader);

    /** Gets the camera's position. @return The camera's position. */
    vec3 get_position();
    /** Sets the camera's position. @param position The new position. */
    void set_position(vec3 position);
    /**
     * Sets the camera's position. 
     * @param x The new x position.
     * @param y The new y position.
     * @param z The new z position. 
     */
    inline void set_position(GLfloat x, GLfloat y, GLfloat z) {set_position(vec3(x,y,z));}

    /** Gets the camera's rotation as (pitch,yaw) in degrees. @return The camera's rotation as (pitch,yaw) in degrees [-180,180]. */
    vec2 get_rotation();
    /** 
     * Sets the camera's rotation as (pitch,yaw) in degrees. 
     * @param pitch The rotation along the local x axis in degrees.
     * @param yaw The rotation along the y axis in degrees.
     */
    void set_rotation(GLfloat pitch, GLfloat yaw);
    /** Sets the camera's rotation as (pitch,yaw) in degrees. @param rotation The new rotation as (pitch,yaw) in degrees [-180,180]. */
    inline void set_rotation(vec2 rotation) { set_rotation(rotation.x,rotation.y); }

    /** Gets the camera's field of view in degrees. @return The camera's field of view. */
    GLfloat get_fov();
    /** Sets the camera's field of view in degrees. @param fov The new field of view. */
    void set_fov(float fov);

    /** Moves the camera by the specified delta. @param delta The delta to move by. */
    void move_by(vec3 delta);
    /** 
     * Moves the camera by the specified delta.
     * @param x The delta to move by on the x axis.
     * @param y The delta to move by on the y axis.
     * @param z The delta to move by on the z axis.
     */
    inline void move_by(GLfloat dx, GLfloat dy, GLfloat dz) {move_by(vec3(dx,dy,dz));}

    /** Moves the camera by the specified delta along it's local x,z and global y axis. @param delta The delta to move by. */
    void move_by_local(vec3 delta);
    /** 
     * Moves the camera by the specified delta along it's local x,z and global y axis.
     * @param x The delta to move by on the local x axis.
     * @param y The delta to move by on the global y axis.
     * @param z The delta to move by on the local z axis.
     */
    inline void move_by_local(GLfloat dx, GLfloat dy, GLfloat dz) {move_by(vec3(dx,dy,dz));}
    

    /** Rotates the camera by the specified delta. @param delta The delta as (pitch,yaw) in degrees [-180,180]. */
    void rotate_by(vec2 delta);
    /** 
     * Rotates the camera by the specified delta.
     * @param dpitch The delta to rotate by on the local x axis in degrees [-180,180].
     * @param dyaw The delta to rotate by on the y axis in degrees [-180,180].
     */
    inline void rotate_by(GLfloat dpitch, GLfloat dyaw) {rotate_by(vec2(dpitch,dyaw));}
    
    /** 
     * Rotates the camera by the specified delta, clamping it vertically to [-90,+90].
     * @param dpitch The delta to rotate by on the local x axis in degrees [-180,180].
     * @param dyaw The delta to rotate by on the y axis in degrees [-180,180].
     */
    void rotate_by_clamped(GLfloat dpitch, GLfloat dyaw);
    /** Rotates the camera by the specified delta, clamping it vertically to [-90,+90]. @param delta The delta as (pitch,yaw) in degrees [-180,180]. */
    inline void rotate_by_clamped(vec2 delta) { rotate_by_clamped(delta.x, delta.y); }
    /** 
     * Rotates the camera by the specified delta, clamping it vertically to [min,max].
     * @param dpitch The delta to rotate by on the local x axis in degrees [-180,180].
     * @param dyaw The delta to rotate by on the y axis in degrees [-180,180].
     */
    void rotate_by_clamped(GLfloat dpitch, GLfloat dyaw, GLfloat min, GLfloat max);
    /** Rotates the camera by the specified delta, clamping it vertically to [min,max]. @param delta The delta as (pitch,yaw) in degrees [-180,180]. */
    inline void rotate_by_clamped(vec2 delta, GLfloat min, GLfloat max) { rotate_by_clamped(delta.x, delta.y, min, max); }

    /** Renders the scene from the camera's point of view. */
    void render();

    /** Destroys the camera object. */
    ~Camera();
};

#endif//_CAMERA_H_