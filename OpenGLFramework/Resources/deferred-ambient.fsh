#version 330

uniform sampler2D uSampler;
uniform vec3 uAmbient;

in vec2 fUV;

out vec4 oColor;

void main() {
    vec4 col = texture(uSampler, fUV);
    oColor = vec4(uAmbient,1) * col;
}