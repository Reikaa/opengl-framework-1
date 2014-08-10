#version 330

uniform mat4 uModelMatrix;
uniform mat4 uViewProjMatrix;

in vec3 vPosition;
in vec2 vTexCoord;

out vec3 fPosition;
out vec2 fTexCoord;

void main() {
    vec4 camPos = uViewProjMatrix * uModelMatrix * vec4(vPosition, 1.0);
    
    fTexCoord = vTexCoord;
    
    gl_Position = camPos;
}