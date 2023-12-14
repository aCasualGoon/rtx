#include "Shader.h"
#include "Includer.h"
#include <iostream>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

const char* read_file(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "File %s not found.\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = new char[length + 1];
    fread(data, 1, length, file);
    data[length] = 0;

    fclose(file);
    return data;
}

bool Shader::create(const char *vertexSourceFile, const char *fragmentSourceFile)
{
    const char *vertexSource = read_file(vertexSourceFile);
    const char *fragmentSource = read_file(fragmentSourceFile);

    // Check if files loaded successfully
    if (vertexSource == NULL) 
    {
        fprintf(stderr, "Could not read vertex shader source file %s\n", vertexSourceFile);
        return false;
    }
    if (fragmentSource == NULL) 
    {
        fprintf(stderr, "Could not read fragment shader source file %s\n", fragmentSourceFile);
        return false;
    }

    // Create the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // parse the files for #include directives
    // vertexSource = Includer::parse(vertexSourceFile);
    // fragmentSource = Includer::parse(fragmentSourceFile);

    // check for include errors
    if (strstr(vertexSource, "SHADER_INCLUDE_ERROR") != NULL)
    {
        fprintf(stderr, "Error parsing vertex shader source file %s\n", vertexSourceFile);
        return false;
    }
    if (strstr(fragmentSource, "SHADER_INCLUDE_ERROR") != NULL)
    {
        fprintf(stderr, "Error parsing fragment shader source file %s\n", fragmentSourceFile);
        return false;
    }

    // Load the source code into the shaders
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

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
    GLint num_uniforms;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &num_uniforms);
    for (GLuint i = 0; i < num_uniforms; i++) {
        GLint size;
        GLenum type;
        char name[256];
        glGetActiveUniform(program, i, 256, NULL, &size, &type, name);
        GLint uniloc = glGetUniformLocation(program, name);
        uniform_locations[name] = glGetUniformLocation(program, name);
    }

    return true;
}

void Shader::use() { glUseProgram(program); }

void Shader::setInt    (const char *name, GLint    value) { glUniform1i (uniform_locations[name], value); }
void Shader::setUInt   (const char *name, GLuint   value) { glUniform1ui(uniform_locations[name], value); }
void Shader::setFloat  (const char *name, GLfloat  value) { glUniform1f (uniform_locations[name], value); }
void Shader::setDouble (const char *name, GLdouble value) { glUniform1d (uniform_locations[name], value); }

void Shader::setInt2   (const char *name, GLint x,GLint y)       { glUniform2i (uniform_locations[name], x, y); }
void Shader::setUInt2  (const char *name, GLuint x,GLuint y)     { glUniform2ui(uniform_locations[name], x, y); }
void Shader::setFloat2 (const char *name, GLfloat x,GLfloat y)   { glUniform2f (uniform_locations[name], x, y); }
void Shader::setFloat2 (const char *name, const vec2 &v )        { glUniform2f (uniform_locations[name], v.x, v.y); }
void Shader::setDouble2(const char *name, GLdouble x,GLdouble y) { glUniform2d (uniform_locations[name], x, y); }

void Shader::setInt3   (const char *name, GLint x,GLint y,GLint z)          { glUniform3i (uniform_locations[name], x, y, z); }
void Shader::setUInt3  (const char *name, GLuint x,GLuint y,GLuint z)       { glUniform3ui(uniform_locations[name], x, y, z); }
void Shader::setFloat3 (const char *name, GLfloat x,GLfloat y,GLfloat z)    { glUniform3f (uniform_locations[name], x, y, z); }
void Shader::setFloat3 (const char *name, const vec3 &v )                   { glUniform3f (uniform_locations[name], v.x, v.y, v.z); }
void Shader::setDouble3(const char *name, GLdouble x,GLdouble y,GLdouble z) { glUniform3d (uniform_locations[name], x, y, z); }

void Shader::setInt4   (const char *name, GLint x,GLint y,GLint z,GLint w)             { glUniform4i (uniform_locations[name], x, y, z, w); }
void Shader::setUInt4  (const char *name, GLuint x,GLuint y,GLuint z,GLuint w)         { glUniform4ui(uniform_locations[name], x, y, z, w); }
void Shader::setFloat4 (const char *name, GLfloat x,GLfloat y,GLfloat z,GLfloat w)     { glUniform4f (uniform_locations[name], x, y, z, w); }
void Shader::setFloat4 (const char *name, const vec4 &v )                              { glUniform4f (uniform_locations[name], v.x, v.y, v.z, v.w); }
void Shader::setDouble4(const char *name, GLdouble x,GLdouble y,GLdouble z,GLdouble w) { glUniform4d (uniform_locations[name], x, y, z, w); }

void Shader::setMatrix (const char *name, const mat2x2 &m) { glUniformMatrix2fv  (uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat2x3 &m) { glUniformMatrix2x3fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat2x4 &m) { glUniformMatrix2x4fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat3x2 &m) { glUniformMatrix3x2fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat3x3 &m) { glUniformMatrix3fv  (uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat3x4 &m) { glUniformMatrix3x4fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat4x2 &m) { glUniformMatrix4x2fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat4x3 &m) { glUniformMatrix4x3fv(uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }
void Shader::setMatrix (const char *name, const mat4x4 &m) { glUniformMatrix4fv  (uniform_locations[name], 1, GL_FALSE, value_ptr(m)); }

Shader::~Shader() { glDeleteProgram(program); }