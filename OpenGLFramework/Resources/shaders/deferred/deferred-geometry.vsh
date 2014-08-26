#version 330

uniform mat4 uModelMatrix;
uniform mat4 uViewProjMatrix;
uniform float uFar;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vTangent;
in vec2 vTexCoord;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;
out float fDepth;
out mat3 fTbnMatrix;

void main() {
    vec4 worldPos = uModelMatrix * vec4(vPosition, 1);
    vec4 worldNormal = uModelMatrix * vec4(vNormal, 0);
    vec4 camPos = uViewProjMatrix * worldPos;
    
    fPosition = worldPos.xyz;
    fTexCoord = vTexCoord;
    
    vec3 normal = normalize((uModelMatrix * vec4(vNormal, 0)).xyz);
    vec3 tangent = normalize((uModelMatrix * vec4(vTangent.xyz, 0)).xyz);
    
    fNormal = normal;
    
    tangent = normalize(tangent-dot(tangent, normal) * normal);
    
    vec3 biTangent = vTangent.w * cross(tangent, normal);
    
    fTbnMatrix = mat3(tangent, biTangent, normal);
    
    gl_Position = camPos;
    fDepth = gl_Position.z / uFar;
}