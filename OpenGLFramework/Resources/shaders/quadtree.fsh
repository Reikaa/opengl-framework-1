#version 330

uniform vec3 uColor;
in vec3 fNormal;

out vec4 oColor;

void main() {
    oColor = vec4(abs(fNormal.x+0.3*fNormal.y+0.5*fNormal.z)*uColor, 0.2);
}