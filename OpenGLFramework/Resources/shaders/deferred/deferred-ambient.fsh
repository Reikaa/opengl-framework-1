#version 330

uniform sampler2D uSampler;
uniform vec3 uAmbientIntensity;

in vec2 fUV;

out vec4 oColor;

void main() {
    vec4 col = texture(uSampler, fUV);
    oColor = vec4(uAmbientIntensity*col.xyz,1);
}