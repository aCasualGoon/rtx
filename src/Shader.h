#ifndef _SHADER_H_
#define _SHADER_H_

#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
using namespace glm;

/** A struct representing a shader program. */
struct Shader {
private:
    std::unordered_map<std::string, GLint> uniform_locations; /** A map of uniform variable names to their locations. */
    GLuint program; /** The OpenGL shader program. */
public:
    /**
     * Creates a shader program from the given vertex and fragment source code files.
     * @param vertexSource The source code file for the vertex shader.
     * @param fragmentSource The source code file for the fragment shader.
     * @return true if the shader program was created successfully, false otherwise.
     */
    bool create(std::string vertexSource, std::string fragmentSource);

    /** Sets this shader program as the current one. */
    void use();

    /**
     * Sets a uniform 32bit integer (glsl:int) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setInt(std::string name, GLint value);

    /**
     * Sets a uniform unsigned 32bit integer (glsl:uint) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setUInt(std::string name, GLuint value);

    /**
     * Sets a uniform float (glsl:float) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setFloat(std::string name, GLfloat value);

    /**
     * Sets a uniform double (glsl:double) value in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setDouble(std::string name, GLdouble value);

    /**
     * Sets two uniform 32bit integer (glsl:ivec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setInt2(std::string name, GLint value1, GLint value2);

    /**
     * Sets two uniform unsigned 32bit integer (glsl:uvec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setUInt2(std::string name, GLuint value1, GLuint value2);

    /**
     * Sets two uniform float (glsl:vec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setFloat2(std::string name, GLfloat value1, GLfloat value2);
    /**
     * Sets two uniform double (glsl:dvec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
    */
    void setFloat2(std::string name, const vec2 &value);

    /**
     * Sets two uniform double (glsl:dvec2) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     */
    void setDouble2(std::string name, GLdouble value1, GLdouble value2);

    /**
     * Sets three uniform 32bit integer (glsl:ivec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setInt3(std::string name, GLint value1, GLint value2, GLint value3);

    /**
     * Sets three uniform unsigned 32bit integer (glsl:uvec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setUInt3(std::string name, GLuint value1, GLuint value2, GLuint value3);

    /**
     * Sets three uniform float (glsl:vec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setFloat3(std::string name, GLfloat value1, GLfloat value2, GLfloat value3);
    /**
     * Sets three uniform float (glsl:vec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setFloat3(std::string name, const vec3 &value);

    /**
     * Sets three uniform double (glsl:dvec3) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     */
    void setDouble3(std::string name, GLdouble value1, GLdouble value2, GLdouble value3);

    /**
     * Sets four uniform 32bit integer (glsl:ivec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setInt4(std::string name, GLint value1, GLint value2, GLint value3, GLint value4);

    /**
     * Sets four uniform unsigned 32bit integer (glsl:uvec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setUInt4(std::string name, GLuint value1, GLuint value2, GLuint value3, GLuint value4);

    /**
     * Sets four uniform float (glsl:vec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setFloat4(std::string name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
    /**
     * Sets four uniform float (glsl:vec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value The value to set.
     */
    void setFloat4(std::string name, const vec4 &value);

    /**
     * Sets four uniform double (glsl:dvec4) values in this shader program.
     * @param name The name of the uniform variable.
     * @param value1 The first value to set.
     * @param value2 The second value to set.
     * @param value3 The third value to set.
     * @param value4 The fourth value to set.
     */
    void setDouble4(std::string name, GLdouble value1, GLdouble value2, GLdouble value3, GLdouble value4);

    /**
     * Sets a 2x2 uniform matrix of float values (glsl:mat2) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat2x2&);

    /**
     * Sets a 2x3 uniform matrix of float values (glsl:mat2x3) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat2x3&);

    /**
     * Sets a 2x4 uniform matrix of float values (glsl:mat2x4) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat2x4&);

    /**
     * Sets a 3x2 uniform matrix of float values (glsl:mat3x2) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat3x2&);

    /**
     * Sets a 3x3 uniform matrix of float values (glsl:mat3) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat3x3&);

    /**
     * Sets a 3x4 uniform matrix of float values (glsl:mat3x4) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat3x4&);

    /**
     * Sets a 4x2 uniform matrix of float values (glsl:mat4x2) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat4x2&);

    /**
     * Sets a 4x3 uniform matrix of float values (glsl:mat4x3) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat4x3&);

    /**
     * Sets a 4x4 uniform matrix of float values (glsl:mat4) in this shader program.
     * @param name The name of the uniform variable.
     * @param value The values to set.
     */
    void setMatrix(std::string name, const mat4x4&);

    /** Cleans up the resources used by this shader program. */
    ~Shader();
};

#endif//_SHADER_H_