#version 420
#include "tracing.glsl"
out vec4 fragColor;
in vec2 uv;
void main() {fragColor = vec4(trace(uv),1.0);}