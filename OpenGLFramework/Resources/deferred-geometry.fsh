#version 330

uniform sampler2D uSampler;

in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fNormal;

layout(location = 0) out vec4 oPos;
layout(location = 1) out vec4 oNormal;
layout(location = 2) out vec4 oColor;

void main() {
    oPos = vec4(fPosition,1);
    oNormal = vec4(fNormal,0);
    oColor = vec4(texture(uSampler, fTexCoord).xyz, 1);
}