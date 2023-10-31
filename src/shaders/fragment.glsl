#version 450
#version 450

out vec4 fragColor;

void main() {
    fragColor = vec4(gl_FragCoord.xy / vec2(1920, 1080), 0.0, 1.0);
}
