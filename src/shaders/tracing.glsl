uniform mat4 cam2world;
uniform vec3 near_clip_data; //(width, height, dist)

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

vec3 frag(vec2 uv) {
    vec4 world_pos = cam2world * vec4(near_clip_data.xy * (uv - 0.5), near_clip_data.z, 1.0);

    Ray ray;
        ray.origin = world_pos.xyz / world_pos.w;
        ray.dir = normalize(ray.origin - cam2world[3].xyz);
        ray.invDir = 1/ray.dir;

    float hitdst = intsec_rayTriangle(ray, vec3(-0.5,-0.5,0.0), vec3(0.0,0.5,0.0), vec3(0.5,-0.5,0.0));
    if(hitdst >= 0)
        return vec3(1.0, 1.0, 1.0);

    return vec3(ray.dir);
}