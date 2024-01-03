struct Ray { vec3 origin; vec3 dir; vec3 invDir; };

#define min3(a,b,c) min(min(a,b),c)
#define max3(a,b,c) max(max(a,b),c)
float intsec_rayAABB(Ray ray, vec3 bbmin, vec3 bbmax) {
    vec3 t1 = (bbmin - ray.origin) * ray.invDir;
    vec3 t2 = (bbmax - ray.origin) * ray.invDir;
    
    vec3 tmin = min(t1, t2);
    vec3 tmax = max(t1, t2);

    float tNear = max3(tmin.x,tmin.y,tmin.z);
    float tFar  = min3(tmax.x,tmax.y,tmax.z);

    if(tNear > tFar || tFar < 0)
        return -1;
    
    return tNear > 0 ? tNear : tFar;
}

// Möller-Trumbore
float intsec_rayTriangle(Ray ray, vec3 a, vec3 b, vec3 c) {
    const float EPSILON = 0.0000001;

    vec3 edge1 = b - a;
    vec3 edge2 = c - a;

    vec3 h = cross(ray.dir, edge2);
    float a_dot_h = dot(edge1, h);

    if(a_dot_h < EPSILON) // parallel or backface
        return -1;

    float f = 1/a_dot_h;
    vec3 s = ray.origin - a;
    float u = f * dot(s, h);

    if(u < 0.0 || u > 1.0)
        return -1;

    vec3 q = cross(s, edge1);
    float v = f * dot(ray.dir, q);

    if(v < 0.0 || u + v > 1.0)
        return -1;

    float t = f * dot(edge2, q);

    if(t > EPSILON)
        return t;
    
    return -1;
}

uniform mat4 cam2world;
uniform vec2 near_clip_data; //(width, height) just used for ray generation, we don't actually clip

vec3 trace(vec2 uv) {
    vec4 world_pos = cam2world * vec4(near_clip_data.xy * (uv - 0.5), 1.0, 1.0);

    Ray ray;
        ray.origin = cam2world[3].xyz;
        ray.dir = normalize(world_pos.xyz/world_pos.w - ray.origin);
        ray.invDir = 1/ray.dir;

    float hitdst = intsec_rayTriangle(ray, vec3(-0.5,-0.5,0.0), vec3(0.0,0.5,0.0), vec3(0.5,-0.5,0.0));
    if(hitdst >= 0)
        return vec3(1.0, 1.0, 1.0);

    return vec3(ray.dir);
}

// #define EPSILON 0.0001

// float frameSDF(vec3 p) {
//     vec3 b = vec3(0.5, 0.5, 0.5);
//     float e = 0.05;
//     p = abs(p  )-b;
//     vec3 q = abs(p+e)-e;
//     return min(min(
//         length(max(vec3(p.x,q.y,q.z),0.0))+min(max(p.x,max(q.y,q.z)),0.0),
//         length(max(vec3(q.x,p.y,q.z),0.0))+min(max(q.x,max(p.y,q.z)),0.0)),
//         length(max(vec3(q.x,q.y,p.z),0.0))+min(max(q.x,max(q.y,p.z)),0.0));
// }

// float sphereSDF(vec3 p) {
//     return length(p) - 0.5;
// }

// float smin(float a, float b, float k) {
//     float h = max(k - abs(a - b), 0.0) / k;
//     return min(a, b) - h * h * h * k * (1.0 / 6.0);
// }

// float sceneSDF(vec3 p) {
//     return smin(frameSDF(p),sphereSDF(p),0.5);
// }

// vec3 estimateNormal(vec3 p) {
//     return normalize(vec3(
//         sceneSDF(vec3(p.x + EPSILON, p.y, p.z)) - sceneSDF(vec3(p.x - EPSILON, p.y, p.z)),
//         sceneSDF(vec3(p.x, p.y + EPSILON, p.z)) - sceneSDF(vec3(p.x, p.y - EPSILON, p.z)),
//         sceneSDF(vec3(p.x, p.y, p.z  + EPSILON)) - sceneSDF(vec3(p.x, p.y, p.z - EPSILON))
//     ));
// }

// vec3 trace(vec2 uv) {
//     vec4 world_pos = cam2world * vec4(near_clip_data.xy * (uv - 0.5), 1.0, 1.0);

//     Ray ray;
//         ray.origin = cam2world[3].xyz;
//         ray.dir = normalize(world_pos.xyz/world_pos.w - ray.origin);
//         ray.invDir = 1/ray.dir;

//     float depth = 0;
//     for(int i = 0; i < 100; i++) {
//         vec3 rayend = ray.origin + ray.dir * depth;
//         float dist = sceneSDF(rayend);
//         if(dist < EPSILON) {
//             float light = dot(estimateNormal(rayend), vec3(0.486664, 0.811107, -0.324443)) * 0.5 + 0.5;
//             return vec3(1.0, 1.0, 1.0) * light;
//         }

//         depth += dist;
//     }

//     return vec3(0.0, 0.0, 0.0);
// }