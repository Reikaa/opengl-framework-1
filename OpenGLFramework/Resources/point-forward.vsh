#version 330

uniform mat4 uModelMatrix;
uniform mat4 uViewProjMatrix;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

void main() {
    vec4 worldPos = uModelMatrix * vec4(vPosition, 1);
    vec4 worldNormal = uModelMatrix * vec4(vNormal, 0);
    vec4 camPos = uViewProjMatrix * worldPos;
    
    fPosition = worldPos.xyz;
    fNormal = worldNormal.xyz;
    fTexCoord = vTexCoord;
    
    gl_Position = camPos;
}