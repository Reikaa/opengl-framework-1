#version 330

#include "material.gls"

out vec4 oColor;
in vec2 fTexCoord;

uniform Material uMaterial;

void main() {
    oColor = texture(uMaterial.sampler, fTexCoord);
}