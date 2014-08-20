#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewProjMatrix;

out vec2 fTexCoord;


void main() {
    gl_Position = (uViewProjMatrix*uModelMatrix*vec4(vPosition,1)).xyww;
    fTexCoord = vTexCoord;
}