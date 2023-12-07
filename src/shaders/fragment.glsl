#version 420
out vec4 fragColor;
vec4 frag();
void main() {fragColor = frag();}

in vec2 uv;

uniform vec3 near_clip_data; //(width, height, dist)
uniform mat4 cam2world;

struct Ray { vec3 origin; vec3 dir; vec3 invDir; };

bool intsec_rayAABB(Ray ray, vec3 bbmin, vec3 bbmax, out float tmin, out float tmax) {
    vec3 t1 = (bbmin - ray.origin) * ray.invDir;
    vec3 t2 = (bbmax - ray.origin) * ray.invDir;
    tmin = max(max(min(t1.x, t2.x), min(t1.y, t2.y)), min(t1.z, t2.z));
    tmax = min(min(max(t1.x, t2.x), max(t1.y, t2.y)), max(t1.z, t2.z));
    return tmax >= tmin;
}

vec4 frag() {
    // if(uv.x < 0) return vec4(1);
    // return vec4(0);

    vec4 world_pos = cam2world * vec4(near_clip_data.xy * (uv - 0.5), near_clip_data.z, 1.0);
    // vec4 world_pos = cam2world * vec4()

    vec3 origin = world_pos.xyz / world_pos.w;
    vec3 dir = normalize(origin - cam2world[3].xyz);

    Ray ray;
        ray.origin = origin;
        ray.dir = dir;
        ray.invDir = 1/dir;

    if(intsec_rayAABB(ray, vec3(0,0, 0.1), vec3(0.3), ray.invDir.x, ray.invDir.y))
        return vec4(1.0, 1.0, 1.0, 1.0);

    return vec4(dir, 1.0);
}
