#version 420
out vec4 fragColor;
vec4 frag();
void main() {fragColor = frag();}

in vec2 uv;

uniform mat4 cam2world;
uniform vec3 near_clip_data; //(width, height, dist)

vec4 frag() {
    vec4 clip_space_pos = vec4(near_clip_data.xy * (uv - 0.5), near_clip_data.z, 1.0);
    vec4 world_pos = cam2world * clip_space_pos;
    vec3 origin = world_pos.xyz / world_pos.w;
    vec3 dir = normalize(origin - cam2world[3].xyz);
    return vec4(dir, 1.0);

    // return vec4(uv, 0.0, 1.0);
}