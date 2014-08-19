#version 330

struct Material {
    sampler2D sampler;
    float specularIntensity;
    float specularPower;
};

uniform Material material;

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
    oColor = vec4(texture(material.sampler, fTexCoord).xyz, 1);
}