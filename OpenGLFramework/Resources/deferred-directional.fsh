#version 330

struct BaseLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    BaseLight base;
    vec3 direction;
};

uniform vec3 uEyePosition;
uniform sampler2D uSamplerPosition;
uniform sampler2D uSamplerNormal;
uniform sampler2D uSamplerColor;

uniform DirectionalLight uDirectionalLight;

in vec2 fUV;

out vec4 oColor;

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal, vec3 fPosition, float specularPower, float specularIntensity) {
    float diffuseFactor = dot(normal, -direction);
    
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    if(diffuseFactor > 0) {
        diffuseColor = vec4(light.color, 1) * light.intensity * diffuseFactor;
        vec3 directionToEye = normalize(uEyePosition - fPosition);
        //vec3 reflectionDirection = normalize(reflect(direction, normal));
        vec3 halfDirection = normalize(directionToEye - direction);
        
        //float specularBase = dot(directionToEye, reflectionDirection);
        float specularBase = dot(halfDirection, normal);
        float specularFactor = pow(specularBase, specularPower);
        
        if(specularFactor > 0) {
            specularColor = vec4(light.color, 1) * specularFactor * specularIntensity;
        }
    }
    
    return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fPosition, float specPower, float specIntensity) {
    return calcLight(light.base, normalize(light.direction), normal, fPosition, specPower, specIntensity);
}

void main() {
    vec4 defPos = texture(uSamplerPosition, fUV);
    vec4 defNormal = texture(uSamplerNormal, fUV);
    vec4 defColor = texture(uSamplerColor, fUV);
    
    if(defNormal.w>=0.99) discard;
    
    oColor = (defColor*calcDirectionalLight(uDirectionalLight, normalize(defNormal.xyz), defPos.xyz, 100, defColor.w));
}