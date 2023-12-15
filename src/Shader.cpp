#include "Shader.h"
#include "shader_loading.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using std::string;
using namespace glm;

bool Shader::create(string vertexSourceFile, string fragmentSourceFile)
{   
    string vertexSource;
    string fragmentSource;
    try {
        vertexSource = loadShaderSource(vertexSourceFile);
        fragmentSource = loadShaderSource(fragmentSourceFile);
    } catch (std::runtime_error &e) {
        fprintf(stderr, "Error loading shader source file: %s\n", e.what());
        return false;
    }

    // Create the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load the source code into the shaders
    const char *vertexSource_ptr = vertexSource.c_str();
    const char *fragmentSource_ptr = fragmentSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource_ptr, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource_ptr, NULL);

    // Compile the shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Check if shaders compiled successfully
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length + 1];
        glGetShaderInfoLog(vertexShader, length, NULL, info);
        fprintf(stderr, "Vertex shader compilation failed:\n%s\n", info);
        delete[] info;
        return false;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length + 1];
        glGetShaderInfoLog(fragmentShader, length, NULL, info);
        fprintf(stderr, "Fragment shader compilation failed:\n%s\n", info);
        delete[] info;
        return false;
    }

    // Link the shaders into a program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check if shaders linked successfully
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length + 1];
        glGetProgramInfoLog(program, length, NULL, info);
        fprintf(stderr, "Shader linking failed:\n%s\n", info);
        delete[] info;
        return false;   
    }

    // Clean up shaders (we don't need them anymore because they are in the program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Populate the uniform_locations map for faster access to uniform variables
    GLint numUniforms = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniforms);
    for (GLint i = 0; i < numUniforms; ++i) {
        const GLsizei bufSize = 64; // Maximum name length
        GLchar name[bufSize]; // Variable for storing the name
        GLsizei length; // Number of chars in the name
        GLint size; // Size of the variable
        GLenum type; // Type of the variable

        glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

        GLint location = glGetUniformLocation(program, name);
        uniform_locations[name] = location;
    }

    return true;
}

void Shader::use() { glUseProgram(program); }

void Shader::setInt    (string name, GLint    value) { glUniform1i (uniform_locations[name], value); }
void Shader::setUInt   (string name, GLuint   value) { glUniform1ui(uniform_locations[name], value); }
void Shader::setFloat  (string name, GLfloat  value) { glUniform1f (uniform_locations[name], value); }
void Shader::setDouble (string name, GLdouble value) { glUniform1d (uniform_locations[name], value); }

void Shader::setInt2   (string name, GLint x,GLint y)       { glUniform2i (uniform_locations[name], x, y); }
void Shader::setUInt2  (string name, GLuint x,GLuint y)     { glUniform2ui(uniform_locations[name], x, y); }
void Shader::setFloat2 (string name, GLfloat x,GLfloat y)   { glUniform2f (uniform_locations[name], x, y); }
void Shader::setFloat2 (string name, const vec2 &v )        { glUniform2f (uniform_locations[name], v.x, v.y); }
void Shader::setDouble2(string name, GLdouble x,GLdouble y) { glUniform2d (uniform_locations[name], x, y); }

void Shader::setInt3   (string name, GLint x,GLint y,GLint z)          { glUniform3i (uniform_locations[name], x, y, z); }
void Shader::setUInt3  (string name, GLuint x,GLuint y,GLuint z)       { glUniform3ui(uniform_locations[name], x, y, z); }
void Shader::setFloat3 (string name, GLfloat x,GLfloat y,GLfloat z)    { glUniform3f (uniform_locations[name], x, y, z); }
void Shader::setFloat3 (string name, const vec3 &v )                   { glUniform3f (uniform_locations[name], v.x, v.y, v.z); }
void Shader::setDouble3(string name, GLdouble x,GLdouble y,GLdouble z) { glUniform3d (uniform_locations[name], x, y, z); }

void Shader::setInt4   (string name, GLint x,GLint y,GLint z,GLint w)             { glUniform4i (uniform_locations[name], x, y, z, w); }
void Shader::setUInt4  (string name, GLuint x,GLuint y,GLuint z,GLuint w)         { glUniform4ui(uniform_locations[name], x, y, z, w); }
void Shader::setFloat4 (string name, GLfloat x,GLfloat y,GLfloat z,GLfloat w)     { glUniform4f (uniform_locations[name], x, y, z, w); }
void Shader::setFloat4 (string name, const vec4 &v )                              { glUniform4f (uniform_locations[name], v.x, v.y, v.z, v.w); }
void Shader::setDouble4(string name, GLdouble x,GLdouble y,GLdouble z,GLdouble w) { glUniform4d (uniform_locations[name], x, y, z, w); }

void Shader::setMatrix (string name, const mat2x2 &m) { glUniformMatrix2fv  (uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat2x3 &m) { glUniformMatrix2x3fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat2x4 &m) { glUniformMatrix2x4fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat3x2 &m) { glUniformMatrix3x2fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat3x3 &m) { glUniformMatrix3fv  (uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat3x4 &m) { glUniformMatrix3x4fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat4x2 &m) { glUniformMatrix4x2fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat4x3 &m) { glUniformMatrix4x3fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (string name, const mat4x4 &m) { glUniformMatrix4fv  (uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }

Shader::~Shader() { glDeleteProgram(program); }