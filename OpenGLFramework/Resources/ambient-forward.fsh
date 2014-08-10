#version 330

uniform vec3 uAmbientIntensity;
uniform sampler2D uSampler;

in vec3 fPosition;
in vec2 fTexCoord;

out vec4 oColor;

void main() {
    oColor = texture(uSampler, fTexCoord) * vec4(uAmbientIntensity, 1);
}