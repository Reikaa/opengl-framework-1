#version 330

out vec4 oColor;
in vec2 fTexCoord;

uniform sampler2D uSkybox;

void main() {
    oColor = texture(uSkybox, fTexCoord);
}