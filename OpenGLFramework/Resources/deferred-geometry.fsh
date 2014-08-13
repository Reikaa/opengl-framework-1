#version 330

uniform sampler2D uSampler;

in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fNormal;

out vec4 oColor;
out vec3 oNormal;


void main() {
    oNormal = fNormal;
    oColor = texture(uSampler, fTexCoord);
}