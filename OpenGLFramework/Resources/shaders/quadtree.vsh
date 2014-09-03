#version 330

uniform mat4 uModelMatrix;
uniform mat4 uViewProjMatrix;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vTangent;
in vec2 vTexCoord;

out vec3 fNormal;

void main() {
    vec4 worldPos = uModelMatrix * vec4(vPosition, 1);
    vec4 worldNormal = uModelMatrix * vec4(vNormal, 0);
    vec4 camPos = uViewProjMatrix * worldPos;
    
    fNormal = worldNormal.xyz;
    
    gl_Position = camPos;
}