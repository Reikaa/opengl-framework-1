#version 330

uniform sampler2D uSampler;

in vec2 fPosition;

out vec4 oColor;

void main() {
    vec2 uv = (vec2(1,1)+fPosition)/2;
    oColor = texture(uSampler, uv);
}