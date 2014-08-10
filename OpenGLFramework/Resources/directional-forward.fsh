#version 330

struct BaseLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    BaseLight base;
    vec3 direction;
};

struct Material {
    float specularIntensity;
    float specularPower;
};

uniform vec3 uEyePosition;
uniform sampler2D sampler;

uniform Material uMaterial;

uniform DirectionalLight uDirectionalLight;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 oColor;

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal) {
    float diffuseFactor = dot(normal, -direction);
    
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    if(diffuseFactor > 0) {
        diffuseColor = vec4(light.color, 1) * light.intensity * diffuseFactor;
        vec3 directionToEye = normalize(uEyePosition - fPosition);
        vec3 reflectionDirection = normalize(reflect(direction, normal));
        
        float specularFactor = pow(dot(directionToEye, reflectionDirection), uMaterial.specularPower);
        
        if(specularFactor > 0) {
            specularColor = vec4(light.color, 1) * specularFactor * uMaterial.specularIntensity;
        }
    }
    
    return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight light, vec3 normal) {
    return calcLight(light.base, light.direction, normal);
}

void main() {
    oColor = texture(sampler, fTexCoord) * calcDirectionalLight(uDirectionalLight, normalize(fNormal));
}