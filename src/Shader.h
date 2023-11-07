#ifndef _SHADER_H
#define _SHADER_H

#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

/** @brief A struct representing a shader program. */
struct Shader {
private:
    GLuint program; /** The OpenGL shader program. */
    std::unordered_map<const char *, GLint> uniform_locations; /** A map of uniform variable names to their locations. */
    /** @brief Populates the uniform_locations map. */
    void populate_uniform_locations();
public:
    /**
     * @brief Creates a shader program from the given vertex and fragment source code files.
     * @param vertexSource The source code file for the vertex shader.
     * @param fragmentSource The source code file for the fragment shader.
     * @return true if the shader program was created successfully, false otherwise.
     */
    bool create(const char *vertexSource, const char *fragmentSource);

    /** @brief Sets this shader program as the current one. */
    void use();

    /**
     * @brief Sets a uniform 32bit integer (glsl:int) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setInt(const char *name, GLint value);

    /**
     * @brief Sets a uniform unsigned 32bit integer (glsl:uint) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setUInt(const char *name, GLuint value);

    /**
     * @brief Sets a uniform float (glsl:float) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setFloat(const char *name, GLfloat value);

    /**
     * @brief Sets a uniform double (glsl:double) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setDouble(const char *name, GLdouble value);

    /**
     * @brief Sets two uniform 32bit integer (glsl:ivec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setInt2(const char *name, GLint value1, GLint value2);

    /**
     * @brief Sets two uniform unsigned 32bit integer (glsl:uvec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setUInt2(const char *name, GLuint value1, GLuint value2);

    /**
     * @brief Sets two uniform float (glsl:vec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setFloat2(const char *name, GLfloat value1, GLfloat value2);
    /**
     * @brief Sets two uniform double (glsl:dvec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
    */
    void setFloat2(const char *name, const vec2 &value);

    /**
     * @brief Sets two uniform double (glsl:dvec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setDouble2(const char *name, GLdouble value1, GLdouble value2);

    /**
     * @brief Sets three uniform 32bit integer (glsl:ivec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setInt3(const char *name, GLint value1, GLint value2, GLint value3);

    /**
     * @brief Sets three uniform unsigned 32bit integer (glsl:uvec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setUInt3(const char *name, GLuint value1, GLuint value2, GLuint value3);

    /**
     * @brief Sets three uniform float (glsl:vec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setFloat3(const char *name, GLfloat value1, GLfloat value2, GLfloat value3);
    /**
     * @brief Sets three uniform float (glsl:vec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setFloat3(const char *name, const vec3 &value);

    /**
     * @brief Sets three uniform double (glsl:dvec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setDouble3(const char *name, GLdouble value1, GLdouble value2, GLdouble value3);

    /**
     * @brief Sets four uniform 32bit integer (glsl:ivec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setInt4(const char *name, GLint value1, GLint value2, GLint value3, GLint value4);

    /**
     * @brief Sets four uniform unsigned 32bit integer (glsl:uvec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setUInt4(const char *name, GLuint value1, GLuint value2, GLuint value3, GLuint value4);

    /**
     * @brief Sets four uniform float (glsl:vec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setFloat4(const char *name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
    /**
     * @brief Sets four uniform float (glsl:vec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setFloat4(const char *name, const vec4 &value);

    /**
     * @brief Sets four uniform double (glsl:dvec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setDouble4(const char *name, GLdouble value1, GLdouble value2, GLdouble value3, GLdouble value4);

    /**
     * @brief Sets a 2x2 uniform matrix of float values (glsl:mat2) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat2x2&);

    /**
     * @brief Sets a 2x3 uniform matrix of float values (glsl:mat2x3) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat2x3&);

    /**
     * @brief Sets a 2x4 uniform matrix of float values (glsl:mat2x4) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat2x4&);

    /**
     * @brief Sets a 3x2 uniform matrix of float values (glsl:mat3x2) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat3x2&);

    /**
     * @brief Sets a 3x3 uniform matrix of float values (glsl:mat3) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat3x3&);

    /**
     * @brief Sets a 3x4 uniform matrix of float values (glsl:mat3x4) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat3x4&);

    /**
     * @brief Sets a 4x2 uniform matrix of float values (glsl:mat4x2) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat4x2&);

    /**
     * @brief Sets a 4x3 uniform matrix of float values (glsl:mat4x3) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat4x3&);

    /**
     * @brief Sets a 4x4 uniform matrix of float values (glsl:mat4) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(const char *name, const mat4x4&);

    /** @brief Cleans up the resources used by this shader program. */
    ~Shader();
};

#endif//_SHADER_H