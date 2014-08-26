#version 330

#include "lighting.gls"

uniform vec3 uEyePosition;
uniform sampler2D uSamplerPosition;
uniform sampler2D uSamplerNormal;
uniform sampler2D uSamplerColor;

uniform DirectionalLight uDirectionalLight;

in vec2 fUV;

out vec4 oColor;

void main() {
    vec4 defPos = texture(uSamplerPosition, fUV);
    vec4 defNormal = texture(uSamplerNormal, fUV);
    vec4 defColor = texture(uSamplerColor, fUV);
    
    oColor = defColor*calcDirectionalLight(uDirectionalLight, uEyePosition, normalize(defNormal.xyz), defPos.xyz, 100, defColor.w);
}