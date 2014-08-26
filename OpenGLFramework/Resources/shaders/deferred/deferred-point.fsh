#version 330

#include "lighting.gls"
#include "deferred.gls"

uniform vec3 uEyePosition;
uniform GeometrySampler uGeometry;
uniform PointLight uPointLight;

in vec2 fUV;

out vec4 oColor;

void main() {
    vec4 defPos = texture(uGeometry.position, fUV);
    vec4 defNormal = texture(uGeometry.normal, fUV);
    vec4 defColor = texture(uGeometry.color, fUV);
    
    oColor = defColor*calcPointLight(uPointLight, uEyePosition, normalize(defNormal.xyz), defPos.xyz, 100, defColor.w);
}