#ifndef _DRAWING_H
#define _DRAWING_H

#include "EngineContext.h"
#include "Shader.h"

//* @brief Draws a quad filling the entire window using the given shader. */
void draw(EngineContext *context, Shader *shader);

#endif//_DRAWING_H