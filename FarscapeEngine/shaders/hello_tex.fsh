#version 410

// FRAGMENT SHADER

in vec2 texCoord0;
in vec3 surfaceNormal;
in vec3 directionToLight;

out vec4 out_color;

uniform sampler2D sampler;
// Light direction should be passed normalized
uniform vec3 lightDirection;
// This is also normalized
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 cameraDirection;


void main(void)
{
    float brightness = clamp(dot(-lightDirection, surfaceNormal), 0.15, 1.0);
    vec3 diffuse = brightness * lightColor;
    
    vec3 lightSrcDirection = -lightDirection;
    vec3 reflectedLightDirection = reflect(lightSrcDirection,surfaceNormal);
    
    float specularFactor = dot(reflectedLightDirection,cameraDirection);
    specularFactor = max(specularFactor,0.0);
    float dampedFactor = pow(specularFactor, shineDamper);
    vec3 specular = dampedFactor * reflectivity * lightColor;
    
    out_color = vec4(diffuse,1.0) * texture(sampler,texCoord0) + vec4(specular,1.0);
}
