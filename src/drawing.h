#ifndef _DRAWING_H
#define _DRAWING_H

#include "EngineContext.h"

void draw(EngineContext *context);

struct Shader
{
private:
    GLuint program;
public:
    Shader(const char *vertexSourceFile, const char *fragmentSourceFile);

    ~Shader();
    void use();
};

// draws a quad on the entire screen using the provided shader
void draw_shader(EngineContext *context, Shader *shader);

#endif//_DRAWING_H