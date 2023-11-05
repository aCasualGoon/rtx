#ifndef _SHADER_H
#define _SHADER_H

#include <GL/glew.h>

/** @brief A struct representing a shader program. */
struct Shader {
private:
    GLuint program; /** The OpenGL shader program. */
    
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

    /** @brief Cleans up the resources used by this shader program. */
    ~Shader();
};

#endif//_SHADER_H