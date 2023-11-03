#version 420
out vec4 fragColor;
vec4 frag();
void main() {fragColor = frag();}

in vec2 uv;

vec4 frag() {
    return vec4(uv, 0.0, 1.0);
}