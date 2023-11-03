#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glew.h>
#include "EngineContext.h"
#include "Shader.h"

class Camera {
private:
    EngineContext *context;
    Shader *shader;
    /*transform matrix*/
    /*projection matrix*/
    /*view matrix*/
    const GLfloat vertices[20] = {
    //    X      Y     Z     U     V
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom left corner
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom right corner
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // Top right corner
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // Top left corner
    };
    const GLuint indices[6] = { 0, 1, 2, 2, 3, 0 };
    GLuint VAO, VBO, EBO;
public:
    Camera(EngineContext *context,Shader *shader);

    void render();

    void cleanup();

    ~Camera() {cleanup();}
};

#endif//_CAMERA_H