#include "Shader.h"
#include <iostream>
#include <GL/glew.h>

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

    // Create the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

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

    return true;
}

void Shader::use() { glUseProgram(program); }

void Shader::cleanup() { glDeleteProgram(program); }