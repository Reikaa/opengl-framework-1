#version 330

in vec3 vPosition;

out vec2 fPosition;

void main() {
    fPosition = vPosition.xy;
    gl_Position = vec4(vPosition.xy, 0,1);
}