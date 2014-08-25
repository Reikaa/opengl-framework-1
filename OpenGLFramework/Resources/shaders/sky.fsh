#version 330

out vec4 oColor;
in vec2 fTexCoord;

struct Material {
    sampler2D sampler;
};

uniform Material uMaterial;

void main() {
    oColor = texture(uMaterial.sampler, fTexCoord);
}