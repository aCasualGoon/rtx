#version 420
out vec4 fragColor;
vec4 frag();
void main() {fragColor = frag();}

in vec2 uv;

uniform vec3 near_clip_data; //(width, height, dist)
uniform mat4 cam2world;

vec4 frag() {
    vec4 world_pos = cam2world * vec4(near_clip_data.xy * (uv - 0.5), near_clip_data.z, 1.0);

    vec3 origin = world_pos.xyz / world_pos.w;
    vec3 dir = normalize(origin - cam2world[3].xyz);
    return vec4(dir, 1.0);
}
