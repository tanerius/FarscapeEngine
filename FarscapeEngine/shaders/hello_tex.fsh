#version 410

in vec2 texCoord0;
in vec3 normal0;

out vec4 out_color;

uniform sampler2D sampler;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;


void main(void)
{
    vec3 unitNormal0 = normalize(normal0);
    vec3 unitLightDirection = normalize(lightDirection);
    float brightness = clamp(dot(-unitLightDirection, unitNormal0), 0.0, 1.0);
    vec3 diffuse = brightness * lightColor;
    out_color = vec4(diffuse,1.0) * texture(sampler,texCoord0);
}
