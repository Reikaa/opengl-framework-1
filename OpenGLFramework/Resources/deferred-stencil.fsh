#version 330

uniform sampler2D uSampler;

in vec2 fUV;

out vec4 oColor;

void main() {
    vec4 col = texture(uSampler, fUV);
    if(col.w != 1) discard;
    oColor = vec4(0,0,0,1);
}