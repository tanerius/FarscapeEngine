#version 410

in vec2 texCoord0;
in vec3 normal0;

out vec4 out_color;

uniform sampler2D sampler;
uniform vec3 lightDirection;

void main(void)
{
    out_color = texture(sampler,texCoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}
