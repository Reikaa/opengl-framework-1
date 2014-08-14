#version 330

in vec3 vPosition;

out vec2 fUV;

void main() {
    fUV = (vec2(1,1)+vPosition.xy)/2;
    gl_Position = vec4(vPosition.xy, 0,1);
}