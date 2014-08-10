#version 330

struct Light {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float diffuseIntensity;
};

struct Material {
    float shininess;
    sampler2D diffuseColor;
    sampler2D emittingColor;
    sampler2D specularColor;
};

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;


uniform vec3 uCameraPosition;
uniform Material uMaterial;
uniform Light uLight;

in vec3 fPosition;
in vec3 fNormal;
in vec4 fColor;
in vec2 fTexCoord;

out vec4 oColor;

void main() {
    vec3 lightDirection = normalize(uLight.position - fPosition);
    vec3 Normal = normalize(fNormal);
    float lambertian = max(dot(lightDirection,Normal), 0.0);
    
    //vec3 Reflection = reflect(-lightDirection, Normal);
    float SpecularFactor = 0.0;
    
    vec4 fDiffuseBase = texture(uMaterial.diffuseColor, fTexCoord);
    vec4 fSpecularBase = texture(uMaterial.specularColor, fTexCoord);
    vec4 fEmittingBase = texture(uMaterial.emittingColor, fTexCoord);
    
    // Ambient
    vec4 AmbientResult = vec4(uLight.color * uLight.ambientIntensity,1) * fDiffuseBase;
    
    // Diffuse
    vec4 DiffuseResult = lambertian * vec4(uLight.color * uLight.diffuseIntensity,1) * fDiffuseBase;
    
    // Specular
    if(lambertian > 0.0 && length(fSpecularBase) > 0.0) {
        vec3 Eye = normalize(uCameraPosition-fPosition);
        vec3 halfDir = normalize(lightDirection + Eye);
        
        //float specAngle = max(dot(Reflection, Eye), 0.0);
        float specAngle = max(dot(halfDir, Normal), 0.0);
        SpecularFactor  = pow(specAngle, uMaterial.shininess * uMaterial.shininess);
    }
    
    vec4 SpecularResult = fSpecularBase * SpecularFactor;
    
    //oColor =  vec4(max(AmbientResult.xyz, max(1.5*fEmittingBase.xyz*fEmittingBase.w, DiffuseResult.xyz)) + SpecularResult.xyz, max(fDiffuseBase.w, 2*SpecularResult.w));
    oColor = vec4(fNormal,1);
}