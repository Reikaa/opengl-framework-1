#version 330

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec2 vTexCoord;

out vec3 fPosition;
out vec3 fNormal;
out vec4 fColor;
out vec2 fTexCoord;

void main() {
    vec4 worldPos = uModelMatrix * vec4(vPosition, 1.0);
    vec4 camPos = uViewMatrix * worldPos;
    vec4 worldNormal = uModelMatrix * vec4(vNormal, 0.0);
    vec4 camNormal = uViewMatrix * worldNormal;
    
    fPosition = worldPos.xyz;
    fNormal = worldNormal.xyz;
    fColor = vColor;
    fTexCoord = vTexCoord;
    
    gl_Position = uProjectionMatrix * camPos;
}