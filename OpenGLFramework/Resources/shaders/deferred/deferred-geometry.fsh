#version 330

#include "material.gls"

uniform Material uMaterial;

in vec3 fPosition;
in vec2 fTexCoord;
in float fDepth;
in mat3 fTbnMatrix;
in vec3 fNormal;


layout(location = 0) out vec4 oPos;
layout(location = 1) out vec4 oNormal;
layout(location = 2) out vec4 oColor;

void main() {
    vec3 texNormal = texture(uMaterial.normal, fTexCoord).xyz;
    vec3 normal = normalize(fTbnMatrix * (255.0/128*texNormal-1));
    
    oPos = vec4(fPosition,1);
    oNormal = vec4(normal,fDepth);
    vec4 color = texture(uMaterial.color, fTexCoord) * (1-uMaterial.coloring.w) + uMaterial.coloring * uMaterial.coloring.w;
    oColor = vec4(color.xyz, uMaterial.specularIntensity);
}