#version 330

#include "material.gls"

uniform Material uMaterial;

in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fNormal;
in float fDepth;


layout(location = 0) out vec4 oPos;
layout(location = 1) out vec4 oNormal;
layout(location = 2) out vec4 oColor;

void main() {
    oPos = vec4(fPosition,1);
    oNormal = vec4(fNormal,fDepth);
    vec4 color = texture(uMaterial.sampler, fTexCoord) * (1-uMaterial.coloring.w) + uMaterial.coloring * uMaterial.coloring.w;
    oColor = vec4(color.xyz, uMaterial.specularIntensity);
}