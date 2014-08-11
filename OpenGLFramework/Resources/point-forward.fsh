#version 330

struct BaseLight {
    vec3 color;
    float intensity;
};

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct PointLight {
    BaseLight base;
    Attenuation attenuation;
    vec3 position;
    float range;
};

struct Material {
    float specularIntensity;
    float specularPower;
};

uniform vec3 uEyePosition;
uniform sampler2D uSampler;

uniform Material uMaterial;

uniform PointLight uPointLight;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 oColor;

float calcAttenuation(Attenuation att, float x) {
    return att.constant + x * att.linear + x*x *att.quadratic;
}

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal) {
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
        float specularFactor = pow(specularBase, 2*uMaterial.specularPower);
        
        if(specularFactor > 0) {
            specularColor = vec4(light.color, 1) * specularFactor * uMaterial.specularIntensity;
        }
    }
    
    return diffuseColor + specularColor;
}

vec4 calcPointLight(PointLight light, vec3 normal) {
    vec3 lightDirection = fPosition - light.position;
    float distanceToLight = length(lightDirection);
    
    if(distanceToLight > light.range)
        return vec4(0,0,0,0);
    
    lightDirection = normalize(lightDirection);
    
    vec4 color = calcLight(light.base, lightDirection, normal);
    float attenuation = abs(calcAttenuation(light.attenuation, distanceToLight))+0.0001;
    
    return color/attenuation;
}

void main() {
    oColor = texture(uSampler, fTexCoord) * calcPointLight(uPointLight, normalize(fNormal));
}