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
    GLuint VAO, VBO, EBO;
public:
    Camera(EngineContext *context,Shader *shader);

    void render();

    void cleanup();

    ~Camera() {cleanup();}
};

#endif//_CAMERA_H