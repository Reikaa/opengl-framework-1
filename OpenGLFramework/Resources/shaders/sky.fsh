#version 330

out vec4 oColor;
in vec2 fTexCoord;

struct Material {
    sampler2D sampler;
};

uniform Material material;

void main() {
    oColor = texture(material.sampler, fTexCoord);
}