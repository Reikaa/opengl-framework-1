#version 330

in vec3 vPosition;
uniform mat4 uViewProjMatrix;

void main() {
    gl_Position = uViewProjMatrix * vec4(vPosition.xy, 0,1);
}